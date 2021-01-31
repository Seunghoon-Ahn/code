#include "ssufs-ops.h"

extern struct filehandle_t file_handle_array[MAX_OPEN_FILES];

int ssufs_allocFileHandle() {
	for(int i = 0; i < MAX_OPEN_FILES; i++) {
		if (file_handle_array[i].inode_number == -1) {
			return i;
		}
	}
	return -1;
}

int max(int a, int b) {
	if(a > b) return a;
	else return b;
}

int ssufs_create(char *filename){
	/* 1 */
	int new_inode;
	int is_exist = open_namei(filename);
	if(is_exist >= 0) //같은 이름의 파일이 존재하는 경우
		return -1;
	new_inode = ssufs_allocInode();
	if(new_inode < 0) //빈 inode가 없을 경우
		return -1;

	struct inode_t *inode_ptr = (struct inode_t *)malloc(sizeof(struct inode_t));
	memset(inode_ptr, 0, sizeof(struct inode_t));
	ssufs_readInode(new_inode, inode_ptr);
	inode_ptr->status = INODE_IN_USE;
	strcpy(inode_ptr->name, filename);
	ssufs_writeInode(new_inode, inode_ptr);
	return new_inode;	
}

void ssufs_delete(char *filename){
	/* 2 */
	int new_inode = open_namei(filename);
	if(new_inode < 0) //없는 것을 지우려할 때
		return;

	for(int i = 0; i < MAX_OPEN_FILES; i++) {
		if(file_handle_array[i].inode_number == new_inode) {
			file_handle_array[i].inode_number == -1;
			break;
		}
	}
	ssufs_freeInode(new_inode);
	return;
}

int ssufs_open(char *filename){
	/* 3 */
	int inodenum = open_namei(filename);
	if(inodenum < 0)
		return -1;
	int cur_fd = ssufs_allocFileHandle();
	if(cur_fd < 0)
		return -1;
	file_handle_array[cur_fd].offset = 0;
	file_handle_array[cur_fd].inode_number = inodenum;
	return cur_fd;
}

void ssufs_close(int file_handle){
	file_handle_array[file_handle].inode_number = -1;
	file_handle_array[file_handle].offset = 0;
}

int ssufs_read(int file_handle, char *buf, int nbytes){
	/* 4 */
	int cur_offset = file_handle_array[file_handle].offset;
	int cur_inode = file_handle_array[file_handle].inode_number;

	struct inode_t *inode_ptr = (struct inode_t *)malloc(sizeof(struct inode_t));

	char *tmp = (char *)malloc(sizeof(char) * BLOCKSIZE * MAX_FILE_SIZE);
	char block_tmp[BLOCKSIZE];

	memset(inode_ptr, 0, sizeof(struct inode_t));
	memset(block_tmp, 0, sizeof(block_tmp));
	memset(tmp, 0, BLOCKSIZE * MAX_FILE_SIZE);
	ssufs_readInode(cur_inode, inode_ptr);
	int filesize = inode_ptr->file_size;

	if(cur_offset + nbytes > filesize) //파일 끝보다 읽어야되는 끝이 넘어갈떄
		return -1;

	for(int i = 0; i <= (filesize-1)/BLOCKSIZE; i++) {
		memset(block_tmp, 0, sizeof(block_tmp));
		ssufs_readDataBlock(inode_ptr->direct_blocks[i], block_tmp);
		memcpy(tmp + i*BLOCKSIZE, block_tmp, BLOCKSIZE);
	}
	memcpy(buf, tmp + cur_offset, nbytes);
	file_handle_array[file_handle].offset += nbytes;

	free(tmp);
	return 0;
}

int ssufs_write(int file_handle, char *buf, int nbytes){
	/* 5 */
	int check_av = 1;
	int cur_offset = file_handle_array[file_handle].offset;
	int cur_inode = file_handle_array[file_handle].inode_number;
	struct inode_t *inode_ptr = (struct inode_t *)malloc(sizeof(struct inode_t));
	char block_tmp[BLOCKSIZE];

	char backup[BLOCKSIZE * MAX_FILE_SIZE];
	char totalfile[BLOCKSIZE * MAX_FILE_SIZE];
	int check_block[MAX_FILE_SIZE];
	memset(inode_ptr, 0, sizeof(struct inode_t));
	memset(backup, 0, sizeof(backup));

	memset(totalfile, 0, sizeof(totalfile));

	ssufs_readInode(cur_inode, inode_ptr);
	int filesize1 = inode_ptr->file_size;
	int filesize2 = cur_offset + nbytes;

	if(filesize2 > BLOCKSIZE * MAX_FILE_SIZE) { //write결과가 최대 파일 크기 이상이 될 경우 펑
		free(inode_ptr);
		return -1;
	}

	for(int i = 0; i <= (filesize1 - 1)/BLOCKSIZE; i++) {
		memset(block_tmp, 0, sizeof(block_tmp));
		ssufs_readDataBlock(inode_ptr->direct_blocks[i], block_tmp);
		memcpy(backup + i*BLOCKSIZE, block_tmp, BLOCKSIZE);
	}//데이터를 다 불러와서 저장


	memcpy(check_block, inode_ptr->direct_blocks, sizeof(check_block));

	int final_block_num = (max(filesize1, filesize2) - 1) / BLOCKSIZE;
	int cur_block_num = (filesize1 - 1) / BLOCKSIZE;

	for(int i = 0; i <= final_block_num; i++) {
		if(inode_ptr->direct_blocks[i] != -1)
			continue;
		int bn = ssufs_allocDataBlock();
		if(bn == -1) {
			check_av = 0;
			break;
		}
		inode_ptr->direct_blocks[i] = bn;
	}
	if(check_av == 0) {
		for(int i = 0; i < MAX_FILE_SIZE; i++) {
			if(inode_ptr->direct_blocks[i] != -1 && check_block[i] == -1)
				ssufs_freeDataBlock(inode_ptr->direct_blocks[i]);
		}
		free(inode_ptr);
		return -1;
	}

	memcpy(totalfile, backup, strlen(backup));
	memcpy(totalfile + cur_offset, buf, nbytes);

	for(int i = 0; i <= final_block_num; i++)
		ssufs_writeDataBlock(inode_ptr->direct_blocks[i], totalfile + i * BLOCKSIZE);

	inode_ptr->file_size = max(filesize1, filesize2);
	file_handle_array[file_handle].offset += nbytes;
	ssufs_writeInode(cur_inode, inode_ptr);

	free(inode_ptr);
	return 0;
}

int ssufs_lseek(int file_handle, int nseek){
	int offset = file_handle_array[file_handle].offset;

	struct inode_t *tmp = (struct inode_t *) malloc(sizeof(struct inode_t));
	ssufs_readInode(file_handle_array[file_handle].inode_number, tmp);
	
	int fsize = tmp->file_size;
	
	offset += nseek;

	if ((fsize == -1) || (offset < 0) || (offset > fsize)) {
		free(tmp);
		return -1;
	}

	file_handle_array[file_handle].offset = offset;
	free(tmp);

	return 0;
}

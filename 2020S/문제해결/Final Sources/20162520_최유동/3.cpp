#include<stdio.h>
#include<queue>
#include<stdio.h>
#include<vector>
#include<string.h>
#define MAX 1121
using namespace std;

bool prnum[MAX];
int vecind[MAX];
vector<int> prlist;

void pr()
{
	prnum[0] = false;
	prnum[1] = false;
	vecind[0] = -1;
	vecind[1] = -1;
	for (int i = 2; i < MAX; i++)
	{
		if (prnum[i])
		{
			prlist.push_back(i);
			vecind[i] = prlist.size() - 1;
			for (int k = 2; i*k < MAX; k++)
			{
				prnum[i*k] = false;
				vecind[i*k] = -1;
			}
		}
	}
}

int solve(vector<int> grp, int min, int res,int ans, int pick, int k)
{
	int ret=0;

	if (pick < k)
	{
		for (int i = min; i < grp.size(); i++)
		{
			if (res + grp[i] <= ans + grp[i]*(k-pick))
			{
				ret += solve(grp, i + 1, res + grp[i], ans, pick + 1, k);
			}
		}
	}
	else
	{
		if (res == ans)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return ret;
}

int main()
{
	vector<int> ans;
	memset(prnum, true, sizeof(prnum));
	pr();
	int T;
	scanf("%d",&T);
	for (int i = 0; i < T; i++)
	{
		int n, k;
		scanf("%d %d", &n, &k);
		vector<int> group;
		int max=0;
		for (int j = n; j > 1; j--)
		{
			if (prnum[j])
			{
				max = j;
				break;
			}
		}
		max = vecind[max];
		for (int i = 0; i <= max; i++)
		{
			group.push_back(prlist[i]);
		}

		ans.push_back(solve(group, 0, 0, n, 0, k));
	}

	for (int i = 0; i < ans.size(); i++)
	{
		printf("%d\n", ans[i]);
	}
}
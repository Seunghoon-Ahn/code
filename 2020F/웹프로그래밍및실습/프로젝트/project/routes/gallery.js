const express = require('express');
const multer = require('multer');
const path = require('path');
const fs = require('fs');

const Gallery = require('../schemas/gallery');
const { isLoggedIn } = require('./middlewares');

const router = express.Router();

try {
  fs.readdirSync('uploads');
} catch (error) {
  console.error('uploads 폴더가 없어 uploads 폴더를 생성합니다.');
  fs.mkdirSync('uploads');
}

const upload = multer({
  storage: multer.diskStorage({
    destination(req, file, cb) {
      cb(null, 'uploads/');
    },
    filename(req, file, cb) {
      const ext = path.extname(file.originalname);
      cb(null, path.basename(file.originalname, ext) + Date.now() + ext);
    },
  }),
  limits: { fileSize: 5 * 1024 * 1024 },
});

router.post('/img', isLoggedIn, upload.single('img'), (req, res) => {
  console.log(req.file);
  res.json({ url: `/img/${req.file.filename}` });
});

const upload2 = multer();
router.post('/', isLoggedIn, upload2.none(), async (req, res, next) => {
  try {
    console.log(req.body);
    let myhashtag = req.body.content.match(/#[^\s#]+/g);
    if(myhashtag) {
      for(let i = 0; i < myhashtag.length; i++)
        myhashtag[i] = myhashtag[i].slice(1).toLowerCase();
    }
    console.log(myhashtag);
    await Gallery.create({
      createdAt: Date.now(),
      img: req.body.url,
      commenterid: req.user.id,
      commenter: req.user.nick,
      hashtags: myhashtag,
    });
    res.redirect('/gallery');
  } catch (error) {
    console.error(error);
    next(error);
  }
});

router.post('/delete', isLoggedIn, async (req, res, next) => {
  try {
    const postid = req.body.postid;
    await Gallery.deleteOne({ _id: postid });
    res.redirect('/gallery');
  } catch (err) {
    console.error(err);
    next(err);
  }
});

router.get('/', async (req, res, next) => {
  try {
    const posts = await Gallery.find({}).sort({createdAt:-1});
    res.render('gallery', {
      title: 'GALLERY',
      twits: posts,
    });
  } catch (err) {
    console.error(err);
    next(err);
  }
});

router.post('/update', isLoggedIn, upload2.none(), async(req, res, next) => {
  console.log(req.body);
  const t_id = req.body.update_id;
  let myhashtag = req.body.content.match(/#[^\s#]+/g);
  if(myhashtag) {
    for(let i = 0; i < myhashtag.length; i++)
      myhashtag[i] = myhashtag[i].slice(1).toLowerCase();
  }
  try {
    console.log(t_id);
    await Gallery.findByIdAndUpdate({'_id': t_id}, {
      $set:{
        img: req.body.url,
        hashtags: myhashtag,

      }
    });
    return res.redirect('/gallery');
  } catch(err) {
    console.error(err);
    return next(err);
  }
});

router.get('/update', isLoggedIn, async(req, res, next) => {
  try {
    const update_post_id = await req.query.postid;
    res.render('gallery-update', {
      title: 'GALLERY - 게시글 수정',
      update_id: update_post_id,
    });
  } catch(err) {
    console.error(err);
    next(err);
  }
});


router.get('/hashtag', isLoggedIn, async(req, res, next) => {
  try {
    const forfind = req.query.hashtag;
    const finded = await Gallery.find({'hashtags': {$in: [forfind]}});
    console.log(finded);
    res.render('gallery', {
      title: 'GALLERY 검색 - ' + forfind,
      twits: finded,
    });
  }  catch(err) {
    console.error(err);
    next(err);
  }
});

module.exports = router;

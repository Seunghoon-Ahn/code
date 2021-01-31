const express = require('express');

const Board = require('../schemas/board');
const User = require("../schemas/user");
const { isLoggedIn } = require('./middlewares');

const router = express.Router();

router.post('/', isLoggedIn, async (req, res, next) => {
  try {
    let myhashtags = req.body.hashtag.match(/#[^\s#]+/g);
    if(myhashtags) {
      for(let i = 0; i < myhashtags.length; i++)
        myhashtags[i] = myhashtags[i].slice(1).toLowerCase();
    }
    await Board.create({
      createdAt: Date.now(),
      title: req.body.title,
      comment: req.body.comment,
      commenterid: req.user.id,
      commenter: req.user.nick,
      hashtags: myhashtags,
    });
    res.redirect('/board');
  } catch (error) {
    console.error(error);
    next(error);
  }
});

router.post('/delete', async (req, res, next) => {
  try {
    const postid = req.body.postid;
    await Board.deleteOne({ _id: postid });
    res.redirect('/board');
  } catch (err) {
    console.error(err);
    next(err);
  }
});

router.get('/', async (req, res, next) => {
  try {
    const comments = await Board.find({}).sort({createdAt:-1});
    res.render('Board', {
      title: 'BOARD',
      twits: comments,
    });
  } catch (err) {
    console.error(err);
    next(err);
  }
});

router.post('/update', isLoggedIn, async(req, res, next) => {
  console.log(req.body);
  const t_id = req.body.update_id;
  let myhashtags = req.body.hashtag.match(/#[^\s#]+/g);
  if(myhashtags) {
    for(let i = 0; i < myhashtags.length; i++)
      myhashtags[i] = myhashtags[i].slice(1).toLowerCase();
  }
  try {
    console.log(t_id);
    await Board.findByIdAndUpdate({'_id': t_id}, {
      $set:{
        title: req.body.title,
        comment: req.body.comment,
        hashtags: myhashtags,
      }
    });
    return res.redirect('/board');
  } catch(err) {
    console.error(err);
    return next(err);
  }
});

router.get('/update', isLoggedIn, async(req, res, next) => {
  try {
    const update_post_id = await req.query.postid;
    res.render('board-update', {
      title: 'BOARD - 게시글 수정',
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
    const finded = await Board.find({'hashtags': {$in: [forfind]}});
    console.log(finded);
    res.render('board', {
      title: 'BOARD 검색 - ' + forfind,
      twits: finded,
    });
  }  catch(err) {
    console.error(err);
    next(err);
  }
});

router.get('/userfind', isLoggedIn, async(req, res, next) => {
  try {
    const forfind = req.query.userfind; //이건 이메일
    const userid = await User.find({'email': forfind});
    const postfromuser = await Board.find({'commenterid': userid[0]._id});
    res.render('board', {
      title: 'BOARD 검색 - ' + forfind,
      twits: postfromuser,
    });
  }  catch(err) {
    console.error(err);
    next(err);
  }
});

router.get('/strfind', isLoggedIn, async(req, res, next) => {
  try {
    const forfind = req.query.strfind;
    const finded = await Board.find({comment: {$regex: forfind}}).sort({createdAt:-1});
    res.render('board', {
      title: 'BOARD 검색 - ' + forfind,
      twits: finded,
    });
  }  catch(err) {
    console.error(err);
    next(err);
  }
});

module.exports = router;
const express = require('express');

const Msg = require('../schemas/msg');
const { isLoggedIn } = require('./middlewares');
const { update } = require('../schemas/board');

const router = express.Router();

router.post('/', isLoggedIn, async (req, res, next) => {
  try {
    console.log(req.body);
    await Msg.create({
      createdAt: Date.now(),
      content: req.body.content,
      sender: req.user.email,
      receiver: req.body.receiver_email,
    });
    res.redirect('/msg');
  } catch (error) {
    console.error(error);
    next(error);
  }
});

router.post('/delete', async (req, res, next) => {
  try {
    const postid = req.body.postid;
    await Msg.deleteOne({ _id: postid });
    res.redirect('/msg');
  } catch (err) {
    console.error(err);
    next(err);
  }
});

router.get('/', async (req, res, next) => {
  try {
    const comments = await Msg.find().where('receiver').equals(req.user.email);
    res.render('msg', {
      title: '메시지 함 - NodeBird',
      twits: comments,
    });
  } catch (err) {
    console.error(err);
    next(err);
  }
});

module.exports = router;
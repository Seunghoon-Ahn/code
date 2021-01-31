const express = require('express');
const { isLoggedIn, isNotLoggedIn } = require('./middlewares');
const Post = require('../schemas/gallery');
const User = require('../schemas/user')

const router = express.Router();

router.use((req, res, next) => {
  res.locals.user = req.user;
  res.locals.followerCount = 0;
  res.locals.followingCount = 0;
  res.locals.followerIdList = [];
  next();
});

router.get('/profile', isLoggedIn, (req, res) => {
  res.render('profile', { title: '내 정보' });
});

router.get('/join', isNotLoggedIn, (req, res) => {
  res.render('join', { title: '회원가입' });
});

router.get('/about', (req, res) => {
  res.render('about', {title: 'About'});
});


router.get('/', (req, res, next) => {
  const twits = [];
  res.render('main', {
    title: 'HOME',
    twits,
  });
});

module.exports = router;

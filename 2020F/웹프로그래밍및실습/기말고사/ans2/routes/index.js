var express = require('express');
var fs= require('fs');
var router = express.Router();
var data = fs.readFileSync('../nyc_weather_data.json', 'utf8');
var words =JSON.parse(data);
var arr = new Array();

const temps = require('../schemas/temps');

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
  //가
  console.log(words[0]);

  //나
  for(var i = 0; i < words.length; i++) {
    var tmp = {'date':words[i].date, 'min':words[i].temperatureMin, 'max':words[i].temperatureMax};
    arr.push(tmp);
  }
  console.log(arr);
});

module.exports = router;

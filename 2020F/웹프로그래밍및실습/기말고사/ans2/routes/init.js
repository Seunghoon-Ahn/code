var express = require('express');
var fs= require('fs');
var router = express.Router();
var data = fs.readFileSync('../nyc_weather_data.json', 'utf8');
var words =JSON.parse(data);
var arr = new Array();

const Temps = require('../schemas/temps');

router.get('/', function(req, res, next) {
    res.render('init', { title: 'Express-init'});
  });


router.post('/', function async(req, res, next) {
  for(var i = 0; i < words.length; i++) {
    var tmp = {'date':words[i].date, 'min':words[i].temperatureMin, 'max':words[i].temperatureMax};
    arr.push(tmp);
  }
  for(var i = 0; i < arr.length; i++) {
    var tmp = {'date':arr[i].date, 'min':arr[i].temperatureMin, 'max':arr[i].temperatureMax};
    const { date, min, max } = tmp;
    Temps.create({
        date,
        min,
        max,
    });
  }
})



module.exports = router;

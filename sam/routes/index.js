var express = require('express');
var router = express.Router();
var jwt = require('express-jwt');
var passport = require('passport');

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});


//sets variables for mongoose schema
var mongoose = require('mongoose');
var User = mongoose.model('User');

var auth = jwt({secret: 'SECRET', userProperty: 'payload'});

// login to the site
router.post('/login', function(req, res, next){
  if(!req.body.username || !req.body.password){
    return res.status(400).json({message: 'Please fill out all fields'});
  }
  passport.authenticate('local', function(err, user, info){
    if(err){ return next(err); }
    if(user){
      return res.json({token: user.generateJWT()});
    } else {
      return res.status(401).json(info);
    }
  })(req, res, next);
});

// register for the site
router.post('/register', function(req, res, next){
  if(!req.body.username || !req.body.password){
    return res.status(400).json({message: 'Please fill out all fields'});
  }
  var user = new User();
  user.username = req.body.username;
  user.setPassword(req.body.password)
  user.save(function (err){
    if(err){ return next(err); }
    return res.json({token: user.generateJWT()})
  });
});


module.exports = router;

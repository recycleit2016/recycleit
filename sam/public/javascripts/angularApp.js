var app = angular.module('recycleIt', ['ui.router']);

app.config([
'$stateProvider',
'$urlRouterProvider',
function($stateProvider, $urlRouterProvider) {

  $urlRouterProvider.otherwise('home');

  $stateProvider
    .state('home', {
      url: '/home',
      templateUrl: '/home.html',
      controller: 'NavCtrl'
    });
  $stateProvider
    .state('bags', {
      url: '/bags',
      templateUrl: '/bags.html',
    });
  $stateProvider
    .state('batteries', {
      url: '/batteries',
      templateUrl: '/batteries.html'
    });
  $stateProvider
    .state('bulbs', {
      url: '/bulbs',
      templateUrl: '/bulbs.html'
    });
  $stateProvider
    .state('cans', {
      url: '/cans',
      templateUrl: '/cans.html'
    });
  $stateProvider
    .state('clothes', {
      url: '/clothes',
      templateUrl: '/clothes.html'
    });
  $stateProvider
    .state('detect', {
      url: '/detect',
      templateUrl: '/detect.html',
      controller: 'MainCtrl'
    });
  $stateProvider
    .state('elec', {
      url: '/elec',
      templateUrl: '/elec.html'
    });
  $stateProvider
    .state('etc', {
      url: '/etc',
      templateUrl: '/etc.html'
    });
  $stateProvider
    .state('glass', {
      url: '/glass',
      templateUrl: '/glass.html'
    });
  $stateProvider
    .state('oil', {
      url: '/oil',
      templateUrl: '/oil.html'
    });
  $stateProvider
    .state('paper', {
      url: '/paper',
      templateUrl: '/paper.html',
      controller: 'MainCtrl'
    });
  $stateProvider
    .state('papercups', {
      url: '/papercups',
      templateUrl: '/papercups.html'
    });
  $stateProvider
    .state('plastic', {
      url: '/plastic',
      templateUrl: '/plastic.html'
    });
  $stateProvider
    .state('search', {
      url: '/search',
      templateUrl: '/search.html'
    });

    //routes to login page
      $stateProvider
        .state('login', {
          url: '/login',
          templateUrl: '/login.html',
          controller: 'AuthCtrl',
          onEnter: ['$state', 'auth', function($state, auth){
            if(auth.isLoggedIn()){
              //$state.go('home');
              console.log('login');
            }
          }]
        });
        //routes to register page
      $stateProvider
        .state('register', {
          url: '/register',
          templateUrl: '/register.html',
          controller: 'AuthCtrl',
          onEnter: ['$state', 'auth', function($state, auth){
            if(auth.isLoggedIn()){
              //$state.go('home');
              console.log('register');
            }
          }]
        });

}]);

//handles authorization and tokens for users
app.factory('auth', ['$http', '$window', '$rootScope', function($http, $window, $rootScope){
   var auth = {
    saveToken: function (token){ //saves token to local storage
      $window.localStorage['sams-forum-token'] = token;
    },
    getToken: function (){ //gets token from local storage
      return $window.localStorage['sams-forum-token'];
    },
    isLoggedIn: function(){
      var token = auth.getToken();

      if(token){
        var payload = JSON.parse($window.atob(token.split('.')[1]));

        return payload.exp > Date.now() / 1000;
      } else {
        return false;
      }
    },
    currentUser: function(){
      if(auth.isLoggedIn()){
        var token = auth.getToken();
        var payload = JSON.parse($window.atob(token.split('.')[1]));

        return payload.username;
      }
    },
    register: function(user){
      return $http.post('/register', user).success(function(data){
        auth.saveToken(data.token);
      });
    },
    logIn: function(user){
      return $http.post('/login', user).success(function(data){
        auth.saveToken(data.token);
      });
    },
    logOut: function(){
      $window.localStorage.removeItem('sams-forum-token');
    }
  };

  return auth;
}])


app.controller('MainCtrl', [
'$scope',
'$state',
'auth',
function($scope, auth){
  $scope.isLoggedIn = auth.isLoggedIn;
  $scope.currentUser = auth.currentUser;
  $scope.countdown = function() {
    var count=10;
    var counter=setInterval(timer, 1000); //1000 will  run it every 1 second
    function timer(){
      count=count-1;
      if (count <= 0){
        clearInterval(counter);
        document.getElementById('bell').play();
        // put code to take a snapshot
        return;
  }
  document.getElementById("countdown").innerHTML=count; // watch for spelling
    }
  }
}]);

//controls registering and logging in
app.controller('AuthCtrl', [
'$scope',
'$state',
'auth',
function($scope, $state, auth){
  $scope.user = {};
  $scope.register = function(){
    auth.register($scope.user).error(function(error){
      $scope.error = error;
    }).then(function(){
      $state.go('home');
    });
  };
  $scope.logIn = function(){
    auth.logIn($scope.user).error(function(error){
      $scope.error = error;
    }).then(function(){
      $state.go('home');
    });
  };
}])
app.controller('NavCtrl', [
'$scope',
'auth',
function($scope, auth){
  $scope.isLoggedIn = auth.isLoggedIn;
  $scope.currentUser = auth.currentUser;
  $scope.logOut = auth.logOut;
}]);

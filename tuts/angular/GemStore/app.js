(function () {
    var app = angular.module('gemStore', ['store-products']);


    /*
    app.controller('StoreController', function () {
        this.products = gems;
    });
    */
    
    
    app.controller('StoreController', ['$http', function($http) {
        var store = this;
        store.products =  [ ];

        $http.get('/api/products').success(function(data){
            store.products = data;
        });
        
    }]);
    

    app.directive('productGallery', function () {
        return {
            restrict: 'E',
            templateUrl: 'product-gallery.html',
            controller: function () {
                this.current = 0;
                this.setCurrent = function (imageNumber) {
                    this.current = imageNumber || 0;
                };
            },
            controllerAs: 'gallery'
        };
    });


    app.directive('productTabs', function () {
        return {
            restrict: 'E',
            templateUrl: 'product-tabs.html',
            controller: function () {
                this.tab = 1;

                this.isSet = function (checkTab) {
                    return this.tab === checkTab;
                };

                this.setTab = function (setTab) {
                    this.tab = setTab;
                };
            },
            controllerAs: 'tab'
        };
    });


    app.controller("ReviewController", function () {

        this.review = {};

        this.addReview = function (product) {
            product.reviews.push(this.review);
            this.review = {};
        };

    });


   




})();

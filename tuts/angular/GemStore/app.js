(function(){
    var app = angular.module('store', [ ]);

    app.controller('StoreController', function() {
        this.products = gems;
    });
	
	
    app.controller('PanelController', function() {
        this.tab = 1;
		
        this.selectTab = function(setTab) {
            this.tab = setTab;
        };
		
        this.isSelected = function(checkTab) {
            return checkTab === this.tab;
        };
    });
	
	
	
    app.controller('TabController', function(){
        this.tab = 1;

        this.setTab = function(newValue){
            this.tab = newValue;
        };

        this.isSet = function(tabName){
            return this.tab === tabName;
        };
    });
	

	
    app.controller('ReviewController', function() {
        this.review = {};
		
        this.addReview = function(product) {
            this.review.createdOn = Date.now();
            product.reviews.push(this.review);
            this.review = {};
        };
    });
	
	
    
    app.directive('productTitle', function () {
        return {
            restrict: 'E',
            templateUrl: 'product-title.html'
        };
    });
    
    

    /*
    app.directive('productTitle', function () {
        return {
            restrict: 'A',
            templateUrl: 'product-title.html'
        };
    });
	*/

	var gems = [
		{
			name: "Craponite",
			price: 2.95,
			description: "24 ounces of pure crap",
			canPurchase: true,
			image: 'gem.png',
			reviews: [
				{
					stars: 5,
					body: "love it",
					author: "aaa@@gmail.com"					
				},
				{
					stars: 1,
					body: "hate it",
					author: "aaa@@gmail.com"					
				},
			],
		},
		{
			name: "Loochohedron",
			price: 3,
			description: "Tough like a diamond",
			canPurchase: true,
			image: 'gem.png',
			reviews: [
				{
					stars: 5,
					body: "pretty..",
					author: "aaa@@gmail.com"					
				},
				{
					stars: 1,
					body: "not so good",
					author: "aaa@@gmail.com"					
				},
			],
		}
	];
	
})();

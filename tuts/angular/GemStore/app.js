(function(){
	var app = angular.module('store', [ ]);

	app.controller('StoreController', function() {
		this.products = gems;
	});
	
	var gems = [
		{
			name: "Craponite",
			price: 2.95,
			description: "24 ounces of pure crap",
			canPurchase: true,
			image: 'gem.png',
		},
		{
			name: "Loochohedron",
			price: 3,
			description: "Tough like a diamond",
			canPurchase: true,
			image: 'gem.png',
		}
	];
	
})();

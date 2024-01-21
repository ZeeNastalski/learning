
console.log("Start");



function Circle(radius, x, y) {
    this.radius = radius;
    this.origin = {x, y};
    this.draw = function() {
        console.log('drawing circle');
    }
    
}

let circle = new Circle(3,1,2);




// for(let k of Object.keys(circle))
//     console.log(k);


let another = Object.assign({}, circle);
let another2 = {...circle};

console.log(circle);

circle.origin.x = 666;
console.log(another);
function arrayFromRange(from, to) {
    let arr = [];
    for(let i = from; i<to; i++) {
        arr.push(i);
    } 
    return arr;      
}


//console.log(`arr: ${arrayFromRange(-1,4)}`);


function includes(array, element) {
    return array.some(x => x === element);
}

//console.log(includes([1,2,3], 0));
//console.log(includes([1,2,3], 1));

function exclude(array, elements) {
    return array.filter( e => !includes(elements, e));
}

//console.log(exclude([1,2,3,4,5,6], [2,2,3,4])) ;

function move(array, position, offset){
    
    const val = array[position];

    if(position + offset > array.length - 1) {
        console.error('Invalid offset');
    }

    if(position + offset < 0) {
        console.error('Invalid offset');
    }

    const arr1 = [...array.slice(0, position), ...array.slice(position+1, array.length)]; 
    const arr2 = [...arr1.slice(0, position+offset), val, ...arr1.slice(position+offset)];
    return arr2;

    
}

// move([1,2,3], 0, 0);
// move([1,2,3], 0, 2);
// move([1,2,3], 2, -2);
// move([1,2,3], 2, -3); //invalid

// console.log(move([1,2,3], 1, 1));
// console.log(move([1,2,3], 1, -1));

function countOccurances(array, number) {
    
    return array.reduce( (a, v) => a + (v===number), 0);
}

//console.log(countOccurances([1,2,3,1,2,3,1,1,2],2));

function max(array) {
    return array.reduce((a,v) => v > a ? v : a);
}

//console.log(max([1,2,42,22,1]));

const movies = [
    {title: 'a', year: 2018, rating: 4.5},
    {title: 'b', year: 2018, rating: 4.7},
    {title: 'c', year: 2018, rating: 3},
    {title: 'd', year: 2017, rating: 4.5},    
];


const filteredMovies = movies
    .filter(x => x.year == 2018 && x.rating > 4)
    .sort((a,b) => a.rating-b.rating)
    .reverse()
    .map(x => x.title);

console.log(filteredMovies);
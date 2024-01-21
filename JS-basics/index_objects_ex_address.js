
console.log("Start: " + new Date());


function Address(street, city, zipcode) {
    this.street = street;
    this.city = city;
    this.zipcode = zipcode;
}

function createAddress(street, city, zipcode){
    return  {
        street, city, zipcode,
    }
}

function showAddress(address) {
    console.log(`type: ${typeof address}, constr: ${address.constructor}`)
    for(let key in address) {
        console.log(`${key} : ${address[key]}`);
    }
}


function areEqual(address1, address2) {
    for(let key in address1) {
        if(address1[key] !== address2[key])
            return false;
    }

    return true;
}

function areSame(address1, address2) {
    return address1 === address2;
}


let addr1 = new Address("404 Bridge St", "Richmond", 3121);
showAddress(addr1);

let addr2 = createAddress("123 Seasame St", "New York", 1234)
showAddress(addr2);

let addr3 = createAddress("123 Seasame St", "New York", 1234)
showAddress(addr2);

console.log(`areEqual: ${areEqual(addr1, addr2)}`);
console.log(`areEqual: ${areEqual(addr2, addr3)}`);


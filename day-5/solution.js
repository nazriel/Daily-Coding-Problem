function cons(a, b)
{
    const pair = (f) => {
        return f(a, b);
    }
    return pair
}

function car(pair)
{
    let result = null;
    pair((a, _) => result = a);
    return result;
}

function cdr(pair)
{
    let result = null;
    pair((_, b) => result = b);
    return result;
}

let result = null;

result = cons(3, 4)((a, b) => a + b);
console.assert(result == 7, result);

result = car(cons(3, 4));
console.assert(result == 3, result);

result = cdr(cons(3, 4));
console.assert(result == 4, result);

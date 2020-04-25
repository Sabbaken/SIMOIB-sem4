export function isPrime(number) {
    if (number < 1 || typeof (number) !== 'number') throw new Error('Type must be prime number!')
    for (let i = 2; i < number; i++) {
        if (number % i === 0) return false
    }
    return number === 2 ? false : true
}

export function toPowAndModulo(base, expo, modulo) {
    const pairsAmount = expo / 2
    let result = 1
    const to = parseInt(pairsAmount.toString())
    for (let index = 0; index < to; index++) {
        result *= Math.pow(base, 2)
        result %= modulo
    }
    if (!Number.isInteger(pairsAmount))
        result *= base
    result %= modulo
    return result
}

export function findBase(power) {
    const getSingles = to => {
        let temp = Array(to - 1).fill().map((_, index) => {
            return index + 1
        })
        return temp;
    }
    if (power < 1 || typeof (power) !== 'number') throw new Error('Type must be prime number!')
    let singles = getSingles(power)
    let results = new Set()
    for (let index = 3; index < power; index++) {
        if (!isPrime(index)) continue
        singles.forEach(val => {
            results.add(toPowAndModulo(index, val, power))
        })
        if (results.size === singles.length) return index
        else results.clear()
    }
}

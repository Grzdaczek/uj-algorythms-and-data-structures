const fs = require('fs')

const pl = fs.readFileSync('./pl.txt').toString().split('\r\n')
const eng = fs.readFileSync('./eng.txt').toString().split('\n')

const zip = (a, b) => a.map((k, i) => [k, b[i]])

const list = zip(pl, eng)
    .filter(([_, e]) => e[0] != 'g' && e[0] != 'G')
    .filter(([p, e]) => 
        !e.includes(' ') && 
        !p.includes(' ') && 
        !e.includes('-'))
    .filter(([p, e]) => p != e)
    .filter(([p, e], i, arr) => {
        if (arr.some(([_, ee], ii) => e == ee && i != ii)) return false;
        if (arr.some(([pp, _], ii) => p == pp && i != ii)) return false;

        return true;
    })
    .map(l => l.join(' '))
    .join('\n')

// console.log(list)
fs.writeFileSync('./slowa.txt', list)
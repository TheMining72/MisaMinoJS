const { MisaMino } = require("../src/index.js");

const c = {
  Reset: "\x1b[0m",

  BgBlack: "\x1b[40m",
  BgRed: "\x1b[41m",
  BgGreen: "\x1b[42m",
  BgYellow: "\x1b[48;5;220m",
  BgOrange: "\x1b[48;5;208m",
  BgBlue: "\x1b[44m",
  BgMagenta: "\x1b[45m",
  BgCyan: "\x1b[46m",
  BgWhite: "\x1b[47m"
}

class piecesGen {
  constructor(seed) {
    this.startSeed = seed % 2147483647;
    this.curSeed = seed % 2147483647;
    this.curBag = 0;
  }

  next() {
    return this.curSeed = 16807 * this.curSeed % 2147483647;
  }

  nextFloat() {
    return (this.next() - 1) / 2147483646;
  }

  nextBag(minos = ["Z", "L", "O", "S", "I", "J", "T"]) {
    this.curBag++;
    let randomPiece, minosLeft = minos.length;

    if (minosLeft == 0) return minos;

    for (;--minosLeft;) {
      randomPiece = Math.floor(this.nextFloat() * (minosLeft + 1));
      [minos[minosLeft], minos[randomPiece]] = [minos[randomPiece], minos[minosLeft]];
    }
    return minos;
  }
}

var queueGen = new piecesGen(1);
var queue = []; queueGen.nextBag().forEach(p => queue.push(p)); queueGen.nextBag().forEach(p => queue.push(p));
var hold = "T";
var current = "I";
var combo = 0;
var b2b = 0;
var field = [];
for (var x = 0; x < 10; x++) {
  field.push([]);
  for (var y = 0; y < 20; y++)
    field[x].push(-1);
}

function printField() {
  console.clear();
  let log = [];

  for (let y = field[0].length - 1; y >= 0; y--) {
    log.push([]);
    for (let x = field.length - 1; x >= 0; x--){
      switch (field[x][y]) {
        case -1:
          log[field[0].length - y - 1].push(c.BgWhite + '  ');
          break;
        case 0:
          log[field[0].length - y - 1].push(c.BgRed + '  ');
          break;
        case 1:
          log[field[0].length - y - 1].push(c.BgGreen + '  ');
          break;
        case 2:
          log[field[0].length - y - 1].push(c.BgOrange + '  ');
          break;
        case 3:
          log[field[0].length - y - 1].push(c.BgBlue + '  ');
          break;
        case 4:
          log[field[0].length - y - 1].push(c.BgMagenta + '  ');
          break;
        case 5:
          log[field[0].length - y - 1].push(c.BgYellow + '  ');
          break;
        case 6:
          log[field[0].length - y - 1].push(c.BgCyan + '  ');
          break;
      }
    }
    log[field[0].length - y - 1].push("\n" + c.Reset);
    log[field[0].length - y - 1] = log[field[0].length - y - 1].join("");
  }
  console.log(log.join(""));
  console.log(`[${hold}] ${current} ${queue.join("")}`);
  console.log(`B2B: ${b2b} Combo: ${combo}`);
}

MisaMino.configure();
var piecesLeft = 14;

async function play() {
  piecesLeft--;
  if (piecesLeft < 7) {
    queueGen.nextBag().forEach(p => queue.push(p));
    piecesLeft += 7;
  }
  MisaMino.update_next(queue);
  MisaMino.update_hold(hold);
  MisaMino.update_current(current);
  MisaMino.update_incoming(0);
  MisaMino.update_combo(combo);
  MisaMino.update_b2b(b2b);
  MisaMino.update_field(field);

  let s = MisaMino.action();
  // 0 = Search everything without taking the pps in
  let pps = 4;
  let actionTimeout;
  if (pps > 0) actionTimeout = setTimeout(MisaMino.abort, Math.floor(1000 / pps))
  s.then(solution => {
    if (pps > 0) clearTimeout(actionTimeout);
    if (solution.Instructions.includes(10))
      hold = current;
    current = queue[0];
    queue.shift();
    new_field = MisaMino.apply_piece(field, solution);
    if (!new_field.Success) {
      console.log("Failed to apply piece")
      return;
    };
    field = new_field.Field;
    if(new_field.Combo) combo++;
    else combo = 0;
    b2b = solution.B2B;

    printField();
    play();
  });
};

console.clear();
play();
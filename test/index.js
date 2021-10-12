console.clear();
const readline = require("readline");
const { MisaMino } = require("../src/index.js");

//  0: Max Depth
// -1: It'll only calculate for the given milliseconds below, set as this if you want a very fast pps
// -2: Literally Max PPS, No calculating at all, it'll do what you think would happen
// Inaccurate though
const PPS = -1;

// Milliseconds to calculate, will be used when PPS = -1
const CALCULATION_MILLISECONDS = 3;

// Piece colors for printField(), not meant to be changed
const PIECE_COLORS = {
  Reset: "\x1b[0m",

  " ": "\x1b[47m  ",
  "G": "\x1b[48;5;239m  ",
  "Z": "\x1b[48;5;196m  ",
  "S": "\x1b[48;5;34m  ",
  "L": "\x1b[48;5;208m  ",
  "J": "\x1b[48;5;20m  ",
  "T": "\x1b[48;5;127m  ",
  "O": "\x1b[48;5;220m  ",
  "I": "\x1b[48;5;50m  "
}

// Random piece generator
class PiecesGen {
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

// Game data
var queueGen = new PiecesGen(1);
var queue = []; queue.push(...queueGen.nextBag()); queue.push(...queueGen.nextBag()); queue.push(...queueGen.nextBag()); queue.push(...queueGen.nextBag()); queue.push(...queueGen.nextBag());
var hold = "T";
var current = "I";
var combo = 0;
var b2b = 0;
var field = [];
for (var x = 0; x < 10; x++) {
  field.push([]);
  for (var y = 0; y < 22; y++)
    field[x].push(" ");
}
field = MisaMino.add_garbage(field, [1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2]);

// Information
var atk = 0;
var piecesPlaced = 0;
var depth = 0;
var startTime = Date.now();
var lastPrintField;

// Prints the field
function printField() {
  let log = [];

  for (let y = field[0].length - 1; y >= 0; y--) {
    log.push([]);
    for (let x = field.length - 1; x >= 0; x--)
      log[field[0].length - y - 1].push(PIECE_COLORS[field[x][y]]);
    log[field[0].length - y - 1].push(PIECE_COLORS.Reset + ' '.repeat(process.stdout.columns - 20));
    log[field[0].length - y - 1] = log[field[0].length - y - 1].join("");
  }
  readline.cursorTo(process.stdout, 0, 0);
  var curSec = (Date.now() - startTime) / 1000;

  console.log(log.join(""));

  queueLog = `[${hold}] ${current} ${queue.join("")}`;
  queueLogSpace = process.stdout.columns - queueLog.length - 1;
  while (queueLogSpace < 0) queueLogSpace += process.stdout.columns;

  depthLog = `Depth: ${depth}`;
  depthLogSpace = process.stdout.columns - depthLog.length - 1;
  while (depthLogSpace < 0) depthLogSpace += process.stdout.columns;

  gameLog = `Combo: ${combo} B2B: ${b2b}`;
  gameLogSpace = process.stdout.columns - gameLog.length - 1;
  while (gameLogSpace < 0) gameLogSpace += process.stdout.columns;

  infoLog = `PPS: ${(piecesPlaced / curSec).toFixed(2)} APP: ${(atk / piecesPlaced).toFixed(2)} APM: ${(atk / (curSec / 60)).toFixed(2)} APS: ${(atk / curSec).toFixed(2)}`;
  infoLogSpace = process.stdout.columns - infoLog.length - 1;
  while (infoLogSpace < 0) infoLogSpace += process.stdout.columns;

  console.log(queueLog, ' '.repeat(queueLogSpace));
  console.log(depthLog, ' '.repeat(depthLogSpace));
  console.log(gameLog, ' '.repeat(gameLogSpace));
  console.log(infoLog, ' '.repeat(infoLogSpace));
}
printField();

// Configure
MisaMino.configure({avoid_softdrop: 0});
let nextBag = queueGen.nextBag();

function play() {
  // Queue
  nextBag.length <= 1 && nextBag.push(...queueGen.nextBag());
  if (queue.length <= 35)
  queue.push(...nextBag.splice(0, 1));

  // Give game data to MisaMinoJS
  MisaMino.update_next(queue);
  MisaMino.update_hold(hold);
  MisaMino.update_current(current);
  MisaMino.update_incoming(0);
  MisaMino.update_combo(combo);
  MisaMino.update_b2b(b2b);
  MisaMino.update_field(field);

  // Start calculating
  let actionPromise = MisaMino.action();
  let actionTimeout;
  if (PPS > 0) actionTimeout = setTimeout(MisaMino.abort, Math.floor(1000 / PPS))

  actionPromise.then(solution => {
    clearTimeout(actionTimeout);

    if (solution != -1) {
      // Field
      newField = MisaMino.apply_piece(field, solution);
      field = newField.Field;

      // Game data
      piecesPlaced++;
      b2b = solution.B2B;
      atk += solution.Attack;
      depth = solution.Depth;
      if(newField.Combo) combo++;
      else combo = 0;

      // Queue & Hold
      if (solution.Instructions.includes(10))
        hold = current;
      current = queue[0];
      queue.shift();

      // Continue if not dead
      printField();
      if (!newField.Success) return;
    }
    play();
  });
  if (PPS == -1) setTimeout(MisaMino.abort, CALCULATION_MILLISECONDS);
  if (PPS < -1) MisaMino.abort();
};

process.on('SIGINT', function() {
  readline.cursorTo(process.stdout, 0, process.stdout.rows);
  process.exit();
});

process.stdout.on("resize", () => {
  console.clear();
  printField();
});

// Start
play();
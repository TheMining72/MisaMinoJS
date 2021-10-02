const MisaMino = require("bindings")("MisaMinoJS");

MisaMino.finished_add(function (...args) {
  console.log(...args);
});

module.exports = {
  MisaMino: MisaMino,
  Pieces: {
    NULL: -1,
    Z: 0,
    S: 1,
    L: 2,
    J: 3,
    T: 4,
    O: 5,
    I: 6,
  },
  Instruction: {
    NULL: 0,
    L: 1,
    R: 2,
    LL: 3,
    RR: 4,
    D: 5,
    DD: 6,
    LSPIN: 7,
    RSPIN: 8,
    DROP: 9,
    HOLD: 10,
    SPIN2: 11,
    REFRESH: 12,
  },
};

const MisaMino = require("bindings")("MisaMinoJS");

action = async () => {
  return new Promise((resolve, reject) => {
    MisaMino.action().then(solution => {
      solution.FinalR = (
        solution.Instructions.filter(s => s == 8).length
        - solution.Instructions.filter(s => s == 7).length
        + solution.Instructions.filter(s => s == 11).length * 2
        + 100
      ) % 4;
      resolve(solution);
    });
  });
}

module.exports = {
  MisaMino: {
    abort: MisaMino.abort,
    configure: MisaMino.configure,
    update_next: MisaMino.update_next,
    update_current: MisaMino.update_current,
    update_hold: MisaMino.update_hold,
    update_incoming: MisaMino.update_incoming,
    update_combo: MisaMino.update_combo,
    update_b2b: MisaMino.update_b2b,
    update_field: MisaMino.update_field,
    update_reset: MisaMino.update_reset,
    action: action,
    alive: MisaMino.alive
  },
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

const MisaMino = require("bindings")("MisaMinoJS");

function action() {
  return new Promise((resolve, reject) => {
    MisaMino.action().then((solution) => {
      solution.FinalR =
        (solution.Instructions.filter((s) => s == 8).length -
          solution.Instructions.filter((s) => s == 7).length +
          solution.Instructions.filter((s) => s == 11).length * 2 +
          100) %
        4;
      resolve(solution);
    });
  });
}

module.exports = {
  MisaMino: {
    ...MisaMino,
    action,
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

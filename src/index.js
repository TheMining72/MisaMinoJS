const fs = require("fs");
const MisaMino = (() => {
  if (fs.existsSync("./build"))
    try {
      return require("bindings")("MisaMinoJS");
    }
    catch (err) {
      console.error("\nFound development build folder but couldn't find the built module, remove the folder to use a prebuilt module.\n");
      throw err;
    }
  else {
    try {
      return require(`../prebuilt/MisaMinoJS-${process.platform}-${process.arch}.node`);
    }
    catch (err) {
      throw new Error("MisaMinoJS is incompatible with your system\n" + err.toString());
    }
  };
})();

function action() {
  return new Promise((resolve, reject) => {
    MisaMino.action().then((solution) => {
      if (solution != -1)
        solution.FinalR =
          (solution.Instructions.reduce((acc, val) => {
            switch (val) {
              case 8:
                acc++;
                break;
              case 7:
                acc--;
                break;
              case 11:
                acc = acc + 2;
                break;
            }
            return acc;
          }, 0) +
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

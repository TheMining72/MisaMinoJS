const { MisaMino } = require("../src/index.js");

MisaMino.configure();
MisaMino.update_next(["Z", "S", "L", "J", "O"]);
MisaMino.update_hold("T");
MisaMino.update_current("I");
MisaMino.update_incoming(0);
MisaMino.update_combo(0);
MisaMino.update_b2b(0);

var field = [];
for (var x = 0; x < 10; x++) {
  field.push([]);
  for (var y = 0; y < 20; y++)
    field[x].push(255);
}
MisaMino.update_field(field);

void async function() {
  console.log(JSON.stringify(await MisaMino.action()));
}();
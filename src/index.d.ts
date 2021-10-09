export interface MisaMino {
  /** Aborts the current action, making it send the best move found while calculating before aborted. */
  abort(): null;

  /**
   * Sets the MisaMino configuration.
   * @param {Partial<MisaMinoParameters>} [param] - The raw MisaMino parameters.
   * @param {boolean} [holdAllowed] - Is holding allowed in the game.
   * @param {boolean} [allSpin] - Is the game awarding spins with all pieces.
   * @param {boolean} [TSDonly] - Are only TSDs allowed (this parameter should only be used for 20 TSD Sprint mode).
   * @param {number} [search_width] - The width multiplier of the AI search per depth. The value 1000 means a regular search.
   * @param {boolean} [allow180] - Are we allowed to use 180 rotations? (TETR.IO kicks)
   * @param {boolean} [srsplus] - Enables the SRS+ system as opposed to using regular SRS.
   */
  configure(
    param?: Partial<MisaMinoParameters>,
    holdAllowed?: boolean,
    allSpin?: boolean,
    TSDonly?: boolean,
    search_width?: number,
    allow180?: boolean,
    srsplus?: boolean
  ): null;

  /** Sets the queue, will be used by the `action` that is called. Doesn't include the piece that is currently falling. */
  update_next(queue: Pieces[]): null;

  /** Sets the current piece, will be used by the `action` that is called. Sets the piece that is currently falling. */
  update_current(piece: Pieces): null;

  /** Sets the held piece, will be used by the `action` that is called. Set as `-1` when none. */
  update_hold(piece?: Pieces | null): null;

  /** Sets the amount of garbage in the garbage meter, will be used by the `action` that is called. */
  update_incoming(attack: number): null;

  /** Sets the current combo, will be used by the `action` that is called. */
  update_combo(combo: number): null;

  /** Sets the current b2b, will be used by the `action` that is called. */
  update_b2b(b2b: number): null;

  /** Updates the current field to be used by action. (The field parameter uses the format `field[x][y]`)  */
  update_field(field: Field): null;

  /** Resets the bot. You need to run configure again after running this. */
  update_reset(): null;

  /** Calculates an action. */
  action(): Promise<Move>;

  /** Is the bot currently alive and hasn't topped out. */
  alive?(): boolean;

  /** Is the bot is currently running. */
  is_running(): boolean;

  /** Applies a piece on to a field based on a move.  */
  apply_piece(
    field: Field,
    solution: Move
  ): { Success: boolean; Field: Field; Combo: boolean };
  /** Applies a piece on to a field based on a piece and it's coordinates.  */
  apply_piece(
    field: Field,
    piece: Pieces,
    x: number,
    y: number,
    z: number
  ): { Success: boolean; Field: Field; Combo: boolean };

  /** Adds a new garbage line for every number in holes, sorted from top to bottom. */
  add_garbage(field: Field, holes: number[]): Field;
}

export interface MisaMinoParameters {
  miny_factor: number;
  hole: number;
  open_hole: number;
  v_transitions: number;
  tspin3: number;
  clear_efficient: number;
  upcomeAtt: number;
  h_factor: number;
  hole_dis_factor2: number;
  hole_dis: number;
  hole_dis_factor: number;
  tspin: number;
  hold_T: number;
  hold_I: number;
  clear_useless_factor: number;
  dif_factor: number;
  b2b: number;
  combo: number;
  avoid_softdrop: number;
  tmini: number;
  strategy_4w: number;
}

export declare type Field = (Pieces | "G" | "")[][];

export declare type Pieces = "Z" | "S" | "L" | "J" | "T" | "O" | "I";

export interface Move {
  /**
   * Gets which piece was used in the Solution.
   */
  PieceUsed: number;
  /**
   * Gets if a spin was used to move the piece numbero position.
   */
  SpinUsed: boolean;
  /**
   * Gets the value of back-to-back after executing the Solution.
   */
  B2B: number;
  /**
   * Gets the number of nodes used in the search. This generally represents how confident MisaMino is in its decision.
   */
  Nodes: number;
  /**
   * Gets how deep the search was able to expand. This represents how many pieces from the queue MisaMino was able to consider in its search.
   */
  Depth: number;
  /**
   * Gets the amount of time, in milliseconds, that the search took to complete.
   */
  Time: number;
  /**
   * Gets the amount of attack garbage executing the decision would send.
   */
  Attack: number;
  /**
   * Gets the final X position of the piece.
   */
  FinalX: number;
  /**
   * Gets the final Y position of the piece.
   */
  FinalY: number;
  /**
   * Gets the final rotation of the piece.
   */
  FinalR: number;
  /**
   * Gets the list of Instructions necessary to correctly place the piece in the desired position.
   */
  Instructions: Instruction[];
}

export declare enum Instruction {
  /**
   * "Don't do anything" instruction. Usually skippable. Often found at the start of an instruction list where using the held piece isn't required.
   */
  NULL = 0,
  /**
   * Move left one tile.
   */
  L = 1,
  /**
   * Move right one tile.
   */
  R = 2,
  /**
   * DAS to left wall.
   */
  LL = 3,
  /**
   * DAS to right wall.
   */
  RR = 4,
  /**
   * Soft drop one tile.
   */
  D = 5,
  /**
   * Soft drop to the ground.
   */
  DD = 6,
  /**
   * Rotate left (counter-clockwise).
   */
  LSPIN = 7,
  /**
   * Rotate right (clockwise).
   */
  RSPIN = 8,
  /**
   * Hard drop piece.
   */
  DROP = 9,
  /**
   * Take the held piece.
   */
  HOLD = 10,
  /**
   * Rotate by 180 degrees.
   */
  SPIN2 = 11,
  /**
   * Refresh (unused).
   */
  REFRESH = 12,
}

export var MisaMino: MisaMino;

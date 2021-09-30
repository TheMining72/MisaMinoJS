{
  "targets": [
    {
      "target_name": "MisaMino",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
        "./src/MisaMinoNET/MisaMinoNET/MisaMino/Bot.cpp"
        "./src/MisaMinoNET/MisaMinoNET/MisaMino/callback.cpp"
        "./src/MisaMinoNET/MisaMinoNET/MisaMino/gamepool.cpp"
        "./src/MisaMinoNET/MisaMinoNET/MisaMino/genmove.cpp"
        "./src/MisaMinoNET/MisaMinoNET/MisaMino/lastnodes.cpp"
        "./src/MisaMinoNET/MisaMinoNET/MisaMino/main.cpp"
        "./src/MisaMinoNET/MisaMinoNET/MisaMino/stuff.cpp"
        "./src/MisaMinoNET/MisaMinoNET/MisaMino/tetris_ai.h"
        "./src/MisaMinoNET/MisaMinoNET/MisaMino/tetris_gem.h"
        "./src/MisaMinoNET/MisaMinoNET/MisaMino/Bot.h"
        "./src/MisaMinoNET/MisaMinoNET/MisaMino/callback.h"
        "./src/MisaMinoNET/MisaMinoNET/MisaMino/gamepool.h"
        "./src/MisaMinoNET/MisaMinoNET/MisaMino/genmove.h"
        "./src/MisaMinoNET/MisaMinoNET/MisaMino/lastnodes.h"
        "./src/MisaMinoNET/MisaMinoNET/MisaMino/main.h"
        "./src/MisaMinoNET/MisaMinoNET/MisaMino/stuff.h"
        "./src/MisaMinoNET/MisaMinoNET/MisaMino/tetris.h"
        "./src/MisaMinoNET/MisaMinoNET/MisaMino/tetris_ai.h"
        "./src/MisaMinoNET/MisaMinoNET/MisaMino/tetris_gem.h"
        "./src/MisaMinoNET/MisaMinoNET/MisaMino/tetris_setting.h"
        "./src/MisaMinoNET/MisaMinoNET/MisaMino/tetrisgame.h"
      ],
      'include_dirs': [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'libraries': [],
      'dependencies': [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    },
    {
      
      "target_name": "MisaMinoJS",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
        "./src/index.cpp"
      ],
      'include_dirs': [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'libraries': [
        "./build/Release/MisaMino.node"
      ],
      'dependencies': [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }
  ]
}
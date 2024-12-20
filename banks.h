#ifndef BANKS_H
#define BANKS_H

const char banks[] PROGMEM = R"=====(
[
    {
      "name": "Iron Maiden",
      "presets": [
        {
          "name": "Clean",
          "onActivate": [
            {
              "type": "control_change",
              "address": 0,
              "value": 0
            },
            {
              "type": "program_change",
              "address": 0
            }
          ],
          "onDeactivate": [
            {
              "type": "control_change",
              "address": 0,
              "value": 127
            }
          ]
        },
        {
          "name": "Rythm",
          "onActivate": [
            {
              "type": "control_change",
              "address": 1,
              "value": 127
            },
            {
              "type": "program_change",
              "address": 1
            }
          ],
          "onDeactivate": [
            {
              "type": "control_change",
              "address": 1,
              "value": 0
            }
          ]
        },
        {
          "name": "Solo",
          "onActivate": [
            {
              "type": "control_change",
              "address": 2,
              "value": 127
            },
            {
              "type": "program_change",
              "address": 2
            }
          ],
          "onDeactivate": [
            {
              "type": "control_change",
              "address": 2,
              "value": 0
            }
          ]
        },
        {
          "name": "Rythm Big",
          "onActivate": [
            {
              "type": "control_change",
              "address": 3,
              "value": 127
            },
            {
              "type": "program_change",
              "address": 3
            }
          ],
          "onDeactivate": [
            {
              "type": "control_change",
              "address": 3,
              "value": 0
            }
          ]
        }
      ]
    },
    {
      "name": "Bank 2",
      "presets": [
        {
          "name": "Preset 1",
          "onActivate": [
            {
              "type": "control_change",
              "channel": 2,
              "address": 64,
              "value": 127
            }
          ],
          "onDeactivate": []
        },
        {
          "name": "Preset 2",
          "onActivate": [],
          "onDeactivate": []
        },
        {
          "name": "Preset 3",
          "onActivate": [],
          "onDeactivate": []
        },
        {
          "name": "Preset 4",
          "onActivate": [],
          "onDeactivate": []
        }
      ]
    }
]
)=====";

#endif

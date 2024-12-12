namespace Parkplatz {

struct Parkplatz {
  int length;
  int ledPfad[8];
  int sensorPfad[8];
};

struct Parkplatz P1 = {2, {10, 1}, {2, 3}};
struct Parkplatz P2 = {2, {10, 12}, {2, 1}};
struct Parkplatz P3 = {3, {10, 9, 2}, {2, 4, 4}};
struct Parkplatz P4 = {3, {10, 9, 13}, {2, 8, 8}};
struct Parkplatz P5 = {3, {10, 9, 3}, {2, 9, 9}};
struct Parkplatz P6 = {3, {10, 9, 14}, {2, 16, 16}};
struct Parkplatz P7 = {4, {10, 9, 8, 4}, {2, 10, 10, 10}};
struct Parkplatz P8 = {4, {10, 9, 8, 15}, {2, 14, 14, 14}};
struct Parkplatz P9 = {4, {10, 9, 8, 5}, {2, 11, 11, 11}};
struct Parkplatz P10 = {4, {10, 9, 8, 16}, {2, 13, 13, 13}};
struct Parkplatz P11 = {4, {11, 24, 25, 23 }, {7, 14, 14, 6 }};
struct Parkplatz P12 = {4, {11, 24, 25, 34 }, {7, 14, 14, 23}};
struct Parkplatz P13 = {5, {11, 24, 25, 26, 22 }, {7, 14, 14, 5, 5}};
struct Parkplatz P14 = {5, {11, 24, 25, 26, 33 }, {7, 14, 14, 22, 22}};
struct Parkplatz P15 = {5, {11, 24, 25, 26, 21 }, {7, 14, 14, 17, 17}};
struct Parkplatz P16  = {5, {11, 24, 25, 26, 32 }, {7, 14, 14, 21, 21}};
struct Parkplatz P17 = {6, {11, 24, 25, 26, 27, 20}, {7, 14, 14, 18, 18, 18 }};
struct Parkplatz P18 =  {6, {11, 24, 25, 26, 27, 31 }, {7, 14, 14, 27, 27, 27 }};
struct Parkplatz P19 = {6, {11, 24, 25, 26, 27, 19 }, {7, 14, 14, 11, 11, 11 }};
struct Parkplatz P20 = {6, {11, 24, 25, 26, 27, 30  }, {7, 14, 14, 28, 28, 28 }};
struct Parkplatz P21 = {6, {11, 24, 35, 36, 46, 37  }, {7, 25, 25, 30, 30, 32 }};
struct Parkplatz P22 = {6, {11, 24, 35, 36, 46, 47  }, {7, 25, 25, 30, 30, 31 }};
struct Parkplatz P23 = {7, {11, 24, 35, 36, 46, 45, 38   }, {7, 25, 25, 30, 30, 36, 36 }};
struct Parkplatz P24 = {7, {11, 24, 35, 36, 46, 45, 48   }, {7, 25, 25, 30, 30, 40, 40 }};
struct Parkplatz P25 = {7, {11, 24, 35, 36, 46, 45, 39   }, {7, 25, 25, 30, 30, 35, 35 }};
struct Parkplatz P26 = {7, {11, 24, 35, 36, 46, 45, 49 }, {7, 25, 25, 30, 30, 29, 29 }};
struct Parkplatz P27 = {8, {11, 24, 35, 36, 46, 45, 44, 40  }, {7, 25, 25, 30, 30, 34, 34, 34 }};
struct Parkplatz P28 = {8, {11, 24, 35, 36, 46, 45, 44, 50  }, {7, 25, 25, 30, 30, 37, 37, 37 }};
struct Parkplatz P29 = {8, {11, 24, 35, 36, 46, 45, 44, 41  }, {7, 25, 25, 30, 30, 33, 33, 33 }};
struct Parkplatz P30 = {8, {11, 24, 35, 36, 46, 45, 44, 51  }, {7, 25, 25, 30, 30, 39, 39, 39 }};

struct Parkplatz allePlaetze[30] = {
P1, P2, P3, P4, P5, P6 ,P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, P18, P19, P20, P21, P22, P23, P24, P25, P26, P27, P28, P29, P30
};

}
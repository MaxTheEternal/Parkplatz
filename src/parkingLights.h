namespace Parkplatz {

struct Parkplatz {
  int length;
  int ledPfad[8];
  int sensorPfad[8];
};

struct Parkplatz P0 = {2, {9, 0}, {1, 2}};
struct Parkplatz P1 = {2, {9, 11}, {1, 0}};
struct Parkplatz P2 = {3, {9, 8, 1}, {1, 3, 3}};
struct Parkplatz P3 = {3, {9, 8, 12}, {1, 7, 7}};
struct Parkplatz P4 = {3, {9, 8, 2}, {1, 8, 8}};
struct Parkplatz P5 = {3, {9, 8, 13}, {1, 15, 15}};
struct Parkplatz P6 = {4, {9, 8, 7, 3}, {1, 9, 9, 9}};
struct Parkplatz P7 = {4, {9, 8, 7, 14}, {1, 13, 13, 13}};
struct Parkplatz P8 = {4, {9, 8, 7, 4}, {1, 10, 10, 10}};
struct Parkplatz P9 = {4, {9, 8, 7, 15}, {1, 12, 12, 12}};
struct Parkplatz P10 = {4, {10, 23, 24, 22 }, {6, 13, 13, 5 }};
struct Parkplatz P11 = {4, {10, 23, 24, 33 }, {6, 13, 13, 22}};
struct Parkplatz P12 = {5, {10, 23, 24, 25, 21 }, {6, 13, 13, 4, 4}};
struct Parkplatz P13 = {5, {10, 23, 24, 25, 32 }, {6, 13, 13, 21, 21}};
struct Parkplatz P14 = {5, {10, 23, 24, 25, 20 }, {6, 13, 13, 16, 16}};
struct Parkplatz P15  = {5, {10, 23, 24, 25, 31 }, {6, 13, 13, 20, 20}};
struct Parkplatz P16 = {6, {10, 23, 24, 25, 26, 19}, {6, 13, 13, 17, 17, 17 }};
struct Parkplatz P17 =  {6, {10, 23, 24, 25, 26, 30 }, {6, 13, 13, 26, 26, 26 }};
struct Parkplatz P18 = {6, {10, 23, 24, 25, 26, 18 }, {6, 13, 13, 10, 10, 10 }};
struct Parkplatz P19 = {6, {10, 23, 24, 25, 26, 29  }, {6, 13, 13, 27, 27, 27 }};
struct Parkplatz P20 = {6, {10, 23, 34, 35, 45, 36  }, {6, 24, 24, 29, 29, 31 }};
struct Parkplatz P21 = {6, {10, 23, 34, 35, 45, 46  }, {6, 24, 24, 29, 29, 30 }};
struct Parkplatz P22 = {7, {10, 23, 34, 35, 45, 44, 37   }, {6, 24, 24, 29, 29, 35, 35 }};
struct Parkplatz P23 = {7, {10, 23, 34, 35, 45, 44, 47   }, {6, 24, 24, 29, 29, 39, 39 }};
struct Parkplatz P24 = {7, {10, 23, 34, 35, 45, 44, 38   }, {6, 24, 24, 29, 29, 34, 34 }};
struct Parkplatz P25 = {7, {10, 23, 34, 35, 45, 44, 48 }, {6, 24, 24, 29, 29, 28, 28 }};
struct Parkplatz P26 = {8, {10, 23, 34, 35, 45, 44, 43, 39  }, {6, 24, 24, 29, 29, 33, 33, 33 }};
struct Parkplatz P27 = {8, {10, 23, 34, 35, 45, 44, 43, 49  }, {6, 24, 24, 29, 29, 36, 36, 36 }};
struct Parkplatz P28 = {8, {10, 23, 34, 35, 45, 44, 43, 40  }, {6, 24, 24, 29, 29, 32, 32, 32 }};
struct Parkplatz P29 = {8, {10, 23, 34, 35, 45, 44, 43, 50  }, {6, 24, 24, 29, 29, 38, 38, 38 }};

struct Parkplatz allePlaetze[30] = {
P0, P1, P2, P3, P4, P5 ,P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, P18, P19, P20, P21, P22, P23, P24, P25, P26, P27, P28, P29
};

}

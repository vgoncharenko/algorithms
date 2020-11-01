//
// Created by Vitaliy on 2019-09-26.
//

#include "repeat-and-missing-number-array.cpp"

void runRepeatAndMissingNumberArrayTest(std::string &variationName, std::vector<int> &A, std::vector<int> &expected) {
  RepeatAndMissingNumberArray *solution = new RepeatAndMissingNumberArray();
  std::vector<int> result = solution->repeatedNumber(A);

  if (result.size() != expected.size()) {
    std::cout << variationName + " FAIL size!" << "\nexpected:" << expected.size() << "\nresult:" << result.size() << std::endl;
  }
  for (int i = 0; i < expected.size(); ++i) {
    if (expected[i] != result[i])
      std::cout << "FAIL " + variationName + ": RepeatAndMissingNumberArray: \nresult[" << i << "] = '" << result[i] << "'\nexpected[" << i << "] = '" << expected[i] << "'" << std::endl;
  }
  std::cout << variationName + " SUCCESS!" << std::endl;
}

void repeatAndMissingNumberArrayTest() {
  std::string variationName;
  std::vector<int> A;
  std::vector<int> expected;

  variationName = "ex0";
  A = {};
  expected = {};
  runRepeatAndMissingNumberArrayTest(variationName, A, expected);

  variationName = "ex1";
  A = {1,2};
  expected = {};
  runRepeatAndMissingNumberArrayTest(variationName, A, expected);

  variationName = "ex2";
  A = {3,1,2,5,3};
  expected = {3,4};
  runRepeatAndMissingNumberArrayTest(variationName, A, expected);

  variationName = "ex3";
  A = {389, 299, 65, 518, 361, 103, 342, 406, 24, 79, 192, 181, 178, 205, 38, 298, 218, 143, 446, 324, 82, 41, 312, 166, 252, 59, 91, 6, 248, 395, 157, 332, 352, 57, 106, 246, 506, 261, 16, 470, 224, 228, 286, 121, 193, 241, 203, 36, 264, 234, 386, 471, 225, 466, 81, 58, 253, 468, 31, 197, 15, 282, 334, 171, 358, 209, 213, 158, 355, 243, 75, 411, 43, 485, 291, 270, 25, 100, 194, 476, 70, 402, 403, 109, 322, 421, 313, 239, 327, 238, 257, 433, 254, 328, 163, 436, 520, 437, 392, 199, 63, 482, 222, 500, 454, 84, 265, 508, 416, 141, 447, 258, 384, 138, 47, 156, 172, 319, 137, 62, 85, 154, 97, 18, 360, 244, 272, 93, 263, 262, 266, 290, 369, 357, 176, 317, 383, 333, 204, 56, 521, 502, 326, 353, 469, 455, 190, 393, 453, 314, 480, 189, 77, 129, 439, 139, 441, 443, 351, 528, 182, 101, 501, 425, 126, 231, 445, 155, 432, 418, 95, 375, 376, 60, 271, 74, 11, 419, 488, 486, 54, 460, 321, 341, 174, 408, 131, 115, 107, 134, 448, 532, 292, 289, 320, 14, 323, 61, 481, 371, 151, 385, 325, 472, 44, 335, 431, 187, 51, 88, 105, 145, 215, 122, 162, 458, 52, 496, 277, 362, 374, 26, 211, 452, 130, 346, 10, 315, 459, 92, 531, 467, 309, 34, 281, 478, 477, 136, 519, 196, 240, 12, 288, 302, 119, 356, 503, 527, 22, 27, 55, 343, 490, 127, 444, 308, 354, 278, 497, 191, 294, 117, 1, 396, 125, 148, 285, 509, 208, 382, 297, 405, 245, 5, 330, 311, 133, 274, 275, 118, 463, 504, 39, 99, 442, 337, 169, 140, 104, 373, 221, 499, 413, 124, 510, 159, 465, 80, 276, 83, 329, 524, 255, 387, 259, 397, 491, 517, 23, 4, 230, 48, 349, 412, 142, 114, 487, 381, 164, 35, 67, 498, 73, 440, 108, 226, 96, 132, 144, 207, 235, 33, 69, 128, 236, 364, 198, 475, 173, 493, 150, 90, 515, 111, 68, 232, 340, 112, 526, 492, 512, 495, 429, 146, 336, 17, 350, 251, 7, 184, 76, 380, 359, 293, 19, 49, 345, 227, 212, 430, 89, 474, 279, 201, 398, 347, 273, 37, 185, 177, 102, 304, 295, 422, 94, 426, 514, 116, 183, 180, 494, 42, 305, 152, 390, 30, 247, 451, 32, 388, 331, 78, 424, 368, 394, 188, 306, 449, 8, 214, 120, 179, 280, 511, 409, 338, 153, 507, 370, 461, 217, 161, 483, 147, 242, 86, 417, 268, 71, 462, 420, 167, 513, 379, 307, 522, 435, 113, 296, 457, 525, 45, 529, 423, 427, 2, 438, 64, 316, 46, 40, 13, 516, 367, 233, 110, 318, 250, 283, 216, 186, 310, 237, 377, 365, 175, 479, 378, 66, 414, 473, 165, 210, 50, 348, 372, 363, 339, 20, 168, 284, 415, 505, 206, 53, 223, 434, 202, 123, 399, 400, 135, 269, 428, 219, 456, 28, 464, 267, 489, 98, 391, 195, 366, 300, 484, 533, 229, 213, 149, 160, 256, 303, 530, 301, 29, 404, 344, 401, 220, 287, 9, 407, 170, 450, 523, 249, 72, 410, 3, 21, 200, 260};
  expected = {213,87};
  runRepeatAndMissingNumberArrayTest(variationName, A, expected);

  variationName = "ex4";
  A = {759, 752, 892, 304, 10, 305, 106, 557, 205, 292, 362, 28, 756, 754, 872, 778, 178, 291, 198, 331, 191, 616, 47, 625, 629, 853, 503, 425, 78, 408, 9, 39, 394, 207, 427, 880, 223, 693, 492, 116, 662, 80, 646, 626, 495, 763, 555, 286, 415, 100, 615, 447, 71, 500, 400, 698, 873, 234, 765, 416, 262, 535, 520, 218, 546, 649, 694, 818, 19, 654, 411, 368, 303, 845, 246, 856, 37, 343, 221, 783, 601, 843, 862, 848, 392, 341, 45, 846, 449, 714, 180, 877, 775, 465, 277, 204, 136, 114, 552, 407, 437, 828, 607, 316, 241, 813, 445, 232, 23, 94, 564, 915, 788, 379, 410, 202, 260, 426, 691, 166, 404, 580, 637, 866, 231, 904, 18, 239, 459, 901, 349, 281, 684, 52, 611, 361, 147, 167, 784, 435, 732, 664, 677, 824, 139, 203, 213, 130, 469, 530, 56, 852, 748, 377, 569, 364, 466, 736, 399, 902, 482, 301, 851, 63, 254, 200, 266, 830, 41, 14, 832, 668, 332, 159, 439, 484, 119, 758, 559, 310, 253, 397, 859, 627, 806, 62, 622, 146, 81, 2, 641, 51, 105, 390, 443, 740, 354, 558, 89, 263, 755, 386, 638, 905, 378, 844, 315, 728, 706, 43, 631, 645, 860, 817, 567, 501, 870, 99, 721, 553, 269, 151, 850, 750, 280, 185, 184, 888, 526, 31, 20, 32, 418, 236, 480, 460, 584, 735, 235, 140, 545, 518, 712, 797, 505, 746, 50, 452, 602, 240, 247, 572, 665, 893, 417, 376, 244, 803, 802, 76, 237, 704, 302, 723, 371, 4, 102, 857, 798, 49, 762, 389, 83, 667, 838, 887, 289, 620, 571, 760, 861, 471, 61, 713, 75, 346, 187, 233, 592, 682, 95, 369, 181, 243, 186, 895, 834, 800, 502, 161, 847, 885, 653, 430, 916, 488, 899, 816, 249, 182, 458, 327, 841, 59, 676, 491, 554, 659, 776, 17, 786, 671, 780, 468, 594, 849, 917, 908, 259, 716, 890, 475, 60, 652, 82, 493, 636, 85, 508, 812, 533, 536, 46, 689, 598, 444, 751, 34, 385, 576, 670, 211, 73, 419, 455, 805, 563, 162, 479, 477, 150, 282, 128, 779, 630, 320, 345, 423, 396, 11, 642, 53, 272, 7, 579, 685, 539, 225, 868, 322, 744, 323, 796, 174, 562, 473, 176, 278, 699, 839, 374, 842, 148, 33, 414, 581, 27, 201, 494, 504, 58, 506, 283, 647, 782, 296, 863, 25, 227, 129, 250, 522, 127, 42, 311, 919, 382, 597, 661, 133, 208, 574, 710, 226, 93, 69, 695, 328, 64, 511, 16, 920, 155, 101, 708, 585, 36, 720, 450, 487, 799, 711, 462, 697, 403, 729, 321, 342, 265, 317, 192, 701, 29, 384, 432, 894, 809, 792, 734, 703, 658, 456, 299, 295, 517, 855, 131, 854, 440, 810, 98, 790, 639, 612, 547, 586, 648, 229, 193, 727, 312, 688, 92, 112, 21, 333, 635, 833, 66, 113, 15, 194, 588, 773, 84, 318, 831, 772, 420, 719, 380, 777, 604, 722, 135, 30, 515, 358, 766, 442, 910, 428, 55, 804, 77, 308, 363, 457, 340, 789, 733, 632, 700, 197, 214, 911, 261, 134, 521, 807, 903, 336, 219, 398, 276, 715, 157, 548, 696, 216, 375, 405, 768, 125, 413, 570, 669, 795, 483, 245, 3, 168, 656, 217, 605, 730, 351, 441, 801, 835, 307, 827, 556, 560, 583, 109, 785, 678, 406, 900, 575, 96, 690, 724, 820, 867, 794, 747, 651, 8, 681, 692, 170, 525, 884, 738, 623, 434, 542, 527, 156, 891, 177, 808, 258, 814, 314, 454, 339, 673, 103, 921, 534, 881, 165, 68, 122, 87, 359, 431, 115, 918, 79, 914, 284, 412, 573, 190, 618, 883, 365, 344, 309, 516, 826, 530, 485, 373, 188, 499, 290, 675, 294, 220, 858, 357, 86, 209, 461, 875, 287, 864, 111, 663, 811, 549, 507, 707, 561, 619, 350, 793, 672, 5, 825, 242, 401, 822, 749, 634, 741, 297, 725, 913, 496, 256, 726, 215, 171, 829, 121, 476, 108, 1, 117, 149, 175, 324, 640, 657, 355, 298, 224, 273, 255, 153, 650, 12, 257, 587, 26, 44, 118, 683, 230, 300, 874, 628, 633, 391, 367, 774, 680, 513, 271, 643, 172, 666, 821, 823, 179, 550, 463, 338, 787, 566, 313, 599, 402, 565, 306, 909, 274, 13, 739, 679, 771, 453, 753, 486, 67, 541, 285, 123, 577, 388, 144, 293, 781, 764, 769, 621, 366, 383, 907, 124, 372, 72, 35, 173, 606, 519, 451, 353, 54, 348, 617, 761, 152, 137, 132, 836, 514, 409, 70, 370, 387, 524, 6, 88, 163, 160, 718, 745, 472, 869, 40, 481, 248, 551, 889, 898, 709, 886, 897, 268, 912, 154, 478, 538, 819, 467, 97, 644, 596, 104, 251, 206, 145, 199, 878, 319, 608, 497, 195, 737, 448, 529, 65, 582, 489, 57, 613, 490, 158, 600, 252, 686, 438, 275, 393, 238, 757, 624, 183, 589, 270, 267, 169, 326, 767, 815, 421, 352, 24, 578, 126, 356, 687, 446, 544, 141, 865, 436, 603, 532, 674, 429, 731, 91, 896, 90, 120, 196, 329, 360, 717, 660, 591, 512, 593, 381, 325, 395, 876, 212, 48, 424, 337, 610, 222, 334, 882, 906, 264, 509, 871, 702, 705, 537, 189, 107, 474, 609, 743, 543, 422, 138, 837, 330, 164, 433, 143, 498, 879, 22, 590, 528, 655, 210, 288, 464, 742, 568, 228, 840, 770, 510, 540, 347, 142, 470, 523, 335, 595, 279, 531, 110, 74, 614, 38};
  expected = {530,791};
  runRepeatAndMissingNumberArrayTest(variationName, A, expected);
}

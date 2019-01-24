#include "time_filling.hpp"
#include "utils.hpp"
#include <random>

#include "time_filling.l.hpp"

using namespace tfl;

std::vector<HexPoint> path_random (std::vector<Hexagon> hexs, HexPoint from, HexPoint to) {

	/* Figure out the links between each hex */

	/*
	
}


HexPath & level1_path (cr <Path> path, cr <Path1> path1, int i) {
	int start, end;
	std::random_device rd;

	if (i == 0) {
		start = 5;
	} else {
		int lastpos = path1[i-1][HEX_PT-1];
		start = rand_start_level1 (path[i-1], lastpos, path[i]);
	}

	if (i == NB_L2) {
		end = 2;  // maybe change this
	} else {
		end = rand_end_level1 (path[i], start, path[i+1]);
	}

stampa_mappa(map_tail, scan);

void stampa_mappa(node* map_tail, player* play){
	node* scan_map;
	node* tmp_map;
	int i, j;
	int min_lon = play->lon() - 3;
	int max_lon = play->lon() + 3;
	int min_lat = play->lat() - 3;
	int max_lat = play->lat() + 3;
	int map[7][7];

	
	for(i=0; i<7; i++){
		for(j=0; j<7; j++){
			map[i][j]=0;
		}
	}

	foreach(map_tail, scan_map, tmp_map){
		if(scan_map->read_x() >= min_lon && scan_map->read_x() <= max_lon && scan_map->read_y() >= min_lat && scan_map->read_y() <= max_lat){
			map[scan_map->read_y()-play->lat()+3][scan_map->read_x()-play->lon()+3] = 1;
		}
		else map[scan_map->read_y()-play->lat()+3][scan_map->read_x()-play->lon()+3] = 0;
	}
	for(i=6; i>=0; i--){
		for(j=0; j<7; j++){
			std::cout << " " << map[i][j] << " ";
		}
		std::cout << "\n";
	}
}
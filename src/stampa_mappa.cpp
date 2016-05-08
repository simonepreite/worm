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

void stampa_mappa(player* scan, node* map_tail){
	int y = 0;
	int x = 0;
	node* scan_map = NULL;
	node* tmp_map = NULL;
	for(y = scan->lat() + 3; y >= scan->lat() - 3; y--){
				cout << "\n------------------------------------------------------------------------------------------------------------------\n";
				cout << "|                |               |               |               |               |               |               |\n";
				cout << "| ";
				for(x = scan->lon() - 3; x <= scan->lon() + 3; x++){
					foreach(map_tail, scan_map, tmp_map){
						if(x == scan_map->read_x() && y == scan_map->read_y()){
							//nodo corrente, dove si trova il player che sta giocando
							if (y == scan->lat() && x == scan->lon()) {
								cout << " |(";
								set_space(scan_map->read_x());
								cout << scan_map->read_x() << ",";
								set_space(scan_map->read_y());
								cout << scan_map->read_y() << ")| ";
							}
							else if (scan_map->busy() != NULL) {
								//nodo nel quale è presente un altro giocatore
								cout << " *(";
								set_space(scan_map->read_x());
								cout << scan_map->read_x() << ",";
								set_space(scan_map->read_y());
								cout << scan_map->read_y() << ")* ";
							}
							else {
								//nodo già creato ma non busy
								cout << "  (";
								set_space(scan_map->read_x());
								cout << scan_map->read_x() << ",";
								set_space(scan_map->read_y());
								cout << scan_map->read_y() << ")  ";
							}
							break;
						}
					}
					if(tmp_map == map_tail) {
						cout << "       0       ";
					}
					cout << "|";
				}
				cout << "\n";
				cout << "|                |               |               |               |               |               |               |";
			}
			cout << "\n------------------------------------------------------------------------------------------------------------------\n";
}
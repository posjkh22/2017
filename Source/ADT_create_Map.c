#include "ADT_create_Map.h"
#include <string.h>
#define MAX_COUNT 10000

#define TRAFFIC

bool calculate_middle_location(FILE *loc_data_fin, float *x_out, float *y_out){

	float x_sum = 0;
	float y_sum = 0;
	
	float x;
	float y;
	int id;
	int count = 0;	

	while(1){

		fscanf(loc_data_fin, "%d", &id); 
		fscanf(loc_data_fin, "%f", &x); 	
		fscanf(loc_data_fin, "%f", &y); 	

		if(feof(loc_data_fin))
			break;
			
		x_sum += x;
		y_sum += y;
		
		count++;

	}
	*x_out = x_sum / count;
	*y_out = y_sum / count;
	
}




bool create_map_html(FILE *loc_data_fin, FILE *cnt_data_fin, FILE *shortest_way_fin){

	FILE *fout = fopen("map.html", "w");


	/* HTML setting data */

	int zoom = 17;
	float line_bold = 3.0;

	char line_color[8] = "#D7DF01";
	char traffic_line_color[MAX_COUNT][8];
	
	char traffic_arr[MAX_COUNT] = {0, };


	float shortest_line_bold = 4.0;
	char shortest_line_color[8] = "#2E64FE";

	
	/* programming data */
	int i = 0; 
	int count = 0;
	int shortest_count = 0;
	int id;
	float data_x, data_y;	
	int from, to;
	int traffic;

	fprintf(fout,"<!DOCTYPE html>\n");
	fprintf(fout,"<html>\n");
	fprintf(fout,"  <head>\n");
	fprintf(fout,"    <meta name=\"viewport\" content=\"initial-scale=1.0, user-scalable=no\">\n");
	fprintf(fout,"    <meta charset=\"utf-8\">\n");
	fprintf(fout,"    <title>Complex icons</title>\n");
	fprintf(fout,"    <style>\n");
	fprintf(fout,"      html, body {\n");
	fprintf(fout,"        height: 100%;\n");
	fprintf(fout,"        margin: 0;\n");
	fprintf(fout,"        padding: 0;\n");
	fprintf(fout,"      }\n");
	fprintf(fout,"      #map {\n");
	fprintf(fout,"        height: 100%;\n");
	fprintf(fout,"      }\n");
	fprintf(fout,"    </style>\n");
	fprintf(fout,"  </head>\n");
	fprintf(fout,"  <body>\n");
	fprintf(fout,"    <div id=\"map\"></div>\n");
	fprintf(fout,"    <script>\n");


	/* calculate middle location */
	rewind(loc_data_fin);
	calculate_middle_location(loc_data_fin, &data_x, &data_y);
	

	fprintf(fout,"function initMap() {\n");
	fprintf(fout,"  var map = new google.maps.Map(document.getElementById('map'), {\n");
	fprintf(fout,"    zoom: %d,\n", zoom);
	fprintf(fout,"    center: {lat: %f, lng: %f}\n", data_x, data_y);
	fprintf(fout,"  });\n");

	fprintf(fout,"  setMarkers(map);\n");

	if(cnt_data_fin)
		fprintf(fout,"  setConnect(map);\n");

	fprintf(fout,"}\n");

	fprintf(fout,"var beaches = [\n");

	rewind(loc_data_fin);
	fscanf(loc_data_fin, "%d", &id);
	fscanf(loc_data_fin, "%f", &data_x);
	fscanf(loc_data_fin, "%f", &data_y);

	if(feof(loc_data_fin))
		return false;

	fprintf(fout,"  ['location %d', %f, %f, %d]", id, data_x, data_y, id);

	while(1){

		fscanf(loc_data_fin, "%d", &id);
		fscanf(loc_data_fin, "%f", &data_x);
		fscanf(loc_data_fin, "%f", &data_y);
		
		if(feof(loc_data_fin))
			break;

		fprintf(fout,",\n");
		fprintf(fout,"  ['location %d', %f, %f, %d]", id, data_x, data_y, id);
	}

	fprintf(fout,"\n];\n");



	/* if there is no connection information */
	/* nothing related is done */
	if(cnt_data_fin){

	rewind(cnt_data_fin);
	rewind(loc_data_fin);

	fprintf(fout,"var cnt = [\n");

		fscanf(cnt_data_fin, "%d", &from); 	
		fscanf(cnt_data_fin, "%d", &to); 	
		fscanf(cnt_data_fin, "%d", &traffic); 	

		traffic_arr[count] = traffic;

		if(feof(cnt_data_fin))
			return false;

		if(feof(loc_data_fin))
			return false;
	
		rewind(loc_data_fin);

		for(i = 0 ; i < from ; i++){
			fscanf(loc_data_fin, "%d", &id);
			fscanf(loc_data_fin, "%f", &data_x);
			fscanf(loc_data_fin, "%f", &data_y);
		}	
		fprintf(fout," [{lat: %f, lng: %f},\n", data_x, data_y);


		rewind(loc_data_fin);

		for(i = 0 ; i < to ; i++){
			fscanf(loc_data_fin, "%d", &id);
			fscanf(loc_data_fin, "%f", &data_x);
			fscanf(loc_data_fin, "%f", &data_y);
		}
		fprintf(fout," {lat: %f, lng: %f}]", data_x, data_y);
	
		count++;

	while(1){


		fscanf(cnt_data_fin, "%d", &from); 	
		fscanf(cnt_data_fin, "%d", &to); 	
		fscanf(cnt_data_fin, "%d", &traffic); 	

		traffic_arr[count] = traffic;

		if(feof(cnt_data_fin))
			break;
	
		fprintf(fout,",\n");

		rewind(loc_data_fin);

		for(i = 0 ; i < from ; i++){
			fscanf(loc_data_fin, "%d", &id);
			fscanf(loc_data_fin, "%f", &data_x);
			fscanf(loc_data_fin, "%f", &data_y);
		}	
		fprintf(fout," [{lat: %f, lng: %f},\n", data_x, data_y);


		rewind(loc_data_fin);

		for(i = 0 ; i < to ; i++){
			fscanf(loc_data_fin, "%d", &id);
			fscanf(loc_data_fin, "%f", &data_x);
			fscanf(loc_data_fin, "%f", &data_y);
		}
		fprintf(fout," {lat: %f, lng: %f}]", data_x, data_y);

		count++;
	}
	
	fprintf(fout,"\n ];\n");

	}
	/* connection related ends */

	/* if there is no shortest way information */
	/* nothing related is done */
	if(shortest_way_fin){

	fprintf(fout,"var shortest_cnt = [\n");

		fscanf(shortest_way_fin, "%d", &from); 	
		fscanf(shortest_way_fin, "%d", &to); 	

		if(feof(shortest_way_fin))
			return false;

		if(feof(loc_data_fin))
			return false;
	
		rewind(loc_data_fin);

		for(i = 0 ; i < from ; i++){
			fscanf(loc_data_fin, "%d", &id);
			fscanf(loc_data_fin, "%f", &data_x);
			fscanf(loc_data_fin, "%f", &data_y);
		}	
		fprintf(fout," [{lat: %f, lng: %f},\n", data_x, data_y);


		rewind(loc_data_fin);

		for(i = 0 ; i < to ; i++){
			fscanf(loc_data_fin, "%d", &id);
			fscanf(loc_data_fin, "%f", &data_x);
			fscanf(loc_data_fin, "%f", &data_y);
		}
		fprintf(fout," {lat: %f, lng: %f}]", data_x, data_y);
	
		shortest_count++;

	while(1){


		fscanf(shortest_way_fin, "%d", &from); 	
		fscanf(shortest_way_fin, "%d", &to); 	

		if(feof(shortest_way_fin))
			break;
	
		fprintf(fout,",\n");

		rewind(loc_data_fin);

		for(i = 0 ; i < from ; i++){
			fscanf(loc_data_fin, "%d", &id);
			fscanf(loc_data_fin, "%f", &data_x);
			fscanf(loc_data_fin, "%f", &data_y);
		}	
		fprintf(fout," [{lat: %f, lng: %f},\n", data_x, data_y);


		rewind(loc_data_fin);

		for(i = 0 ; i < to ; i++){
			fscanf(loc_data_fin, "%d", &id);
			fscanf(loc_data_fin, "%f", &data_x);
			fscanf(loc_data_fin, "%f", &data_y);
		}
		fprintf(fout," {lat: %f, lng: %f}]", data_x, data_y);

		shortest_count++;
	}
	
	fprintf(fout,"\n ];\n");

	}
	/* shortest path related ends */

	fprintf(fout,"function setMarkers(map) {\n");


	fprintf(fout,"  var image = {\n");
	fprintf(fout,"    url: 'https://photos-5.dropbox.com/t/2/AAC5H1Zz55nKyk2KED2qFJVwg_QXcMyDrLeQcSFgW_Lc3g/12/614940094/png/32x32/1/_/1/2/flag.png/ELjLzfwEGNnIAiAHKAc/2zMJJLpXfQGRtRvtVcJyfRHC1jeFUWnJTrKhK7mpOWQ?size=1600x1200&size_mode=3',\n");
	fprintf(fout,"    size: new google.maps.Size(32, 32),\n");
	fprintf(fout,"    origin: new google.maps.Point(0, 0),\n");
	fprintf(fout,"    anchor: new google.maps.Point(5, 5)\n");
	fprintf(fout,"  };\n");
	fprintf(fout,"  var shape = {\n");
	fprintf(fout,"    coords: [1, 1, 1, 20, 18, 20, 18, 1],\n");
	fprintf(fout,"    type: 'poly'\n");
	fprintf(fout,"  };\n");

	fprintf(fout,"  for (var i = 0; i < beaches.length; i++) {\n");
	fprintf(fout,"    var beach = beaches[i];\n");
	fprintf(fout,"    var marker = new google.maps.Marker({\n");
	fprintf(fout,"      position: {lat: beach[1], lng: beach[2]},\n");
	fprintf(fout,"      map: map,\n");
	fprintf(fout,"      icon: image,\n");
	fprintf(fout,"      shape: shape,\n");
	fprintf(fout,"      title: beach[0],\n");
	fprintf(fout,"      zIndex: beach[3]\n");
	fprintf(fout,"    });\n");
	fprintf(fout,"  }\n");
	fprintf(fout,"}\n");

	
	/* if there is no connection information */
	/* nothing related is done */
	if(cnt_data_fin){


	/* color setting as to traffic */
	for(i = 0; i<count; i++){

		if( 0 < traffic_arr[i] && traffic_arr[i] <= 64){	
			strcpy(traffic_line_color[i], "#40FF00");
		}

		else if( 64 < traffic_arr[i] && traffic_arr[i] <= 128){
			strcpy(traffic_line_color[i], "#BFFF00");
		}
		
		else if( 128 < traffic_arr[i] && traffic_arr[i] <= 192){
			strcpy(traffic_line_color[i], "#FF8000");
		}	
	
		else{
			strcpy(traffic_line_color[i], "#FF0000");
		}		
		
	}

	fprintf(fout,"function setConnect(map){\n");

	for(i = 0; i<count; i++){
		fprintf(fout,"      var poly%d = new google.maps.Polyline({\n", i);
		fprintf(fout,"        path: cnt[%d],\n", i);

		#ifdef TRAFFIC
		fprintf(fout,"        strokeColor: '%s',\n", traffic_line_color[i]);
		#endif

		#ifndef TRAFFIC
		fprintf(fout,"        strokeColor: '%s',\n", line_color);
		#endif

		fprintf(fout,"        strokeWeight: %f\n", line_bold);
		fprintf(fout,"      });\n");
	}

	for(i = 0; i<count; i++){
		fprintf(fout,"      poly%d.setMap(map);\n", i);
	}


	/* if there is no shortest way information */
	/* nothing related is done */
	if(shortest_way_fin){

		for(i = 0; i<shortest_count;i++){
			fprintf(fout,"      var shortest_path%d = new google.maps.Polyline({\n", i);
			fprintf(fout,"        path: shortest_cnt[%d],\n", i);
			fprintf(fout,"        strokeColor: '%s',\n", shortest_line_color);
			fprintf(fout,"        strokeWeight: %f\n", shortest_line_bold);
			fprintf(fout,"      });\n");
		}

	}

	if(shortest_way_fin){
		for(i = 0; i<shortest_count; i++){
			fprintf(fout,"      shortest_path%d.setMap(map);\n", i);
		}

	}

	fprintf(fout,"}\n");

	}
	/* connection related ends */

	fprintf(fout,"    </script>\n");
	fprintf(fout,"    <script async defer\n");
	fprintf(fout,"        src=\"https://maps.googleapis.com/maps/api/js?key=AIzaSyDq8LSOsyk1mdiRuLjLGWl0EHKZWKhP32c&callback=initMap\"></script>\n");
	fprintf(fout,"  </body>\n");
	fprintf(fout,"</html>\n");


	fclose(fout);
}

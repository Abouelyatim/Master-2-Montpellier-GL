#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>



typedef struct Parck {
  const char *id;
  const char *name;
  const char *path;
  const float lat;
  const float lon;
} Parck;

const Parck data [22] = {
  { 
  	"34172_ANTIGO",
	"Antigone", 
	"FR_MTP_ANTI",
	3.88881893, 
	43.6087160 

  },
  {
     "34172_ARCTRI",
     "Arc de Triomphe",
     "FR_MTP_ARCT",
     3.87320075,
     43.61100267
  },
  {
     "34172_TRIANG",
     "Triangle",
     "FR_MTP_TRIA",
     3.88184418,
     43.60923384
  },
  {
     "34172_PITOT",
     "Pitot",
     "FR_MTP_PITO",
     3.87019117,
     43.61224494
  },
  {
  	 "34057_SABLAS",
	 "Notre Dame de Sablassou",
	 "FR_CAS_SABL",
	 3.922295360000000, 
	 43.634191940000001
  },
  { 
  	 "34172_CIRCE",
	 "Circé Odysseum",
	 "FR_MTP_CIRC", 
	 3.917849500000000,
	 43.604953770000002 
  },
  {
     "34172_ARCEAU",
     "Arceaux",
     "FR_MTP_ARCE",
     3.86749067,
     43.61171647
  },
  {
     "34172_GAMBET",
     "Gambetta",
     "FR_MTP_GAMB",
     3.87137436,
     43.60695138
  },
  {
     "34172_FOCHPR",
     "Foch Préfecture",
     "FR_MTP_FOCH",
     3.87657084,
     43.61074912
  },
  {
     "34172_COMEDI",
     "Comédie",
     "FR_MTP_COME",
     3.87976196,
     43.60856092
  },
  {
     "34172_POLYGO",
     "Polygone",
     "FR_MTP_POLY",
     3.88476539,
     43.60837096
  },
  {
     "34172_ANTIGO",
     "Antigone",
     "FR_MTP_ANTI",
     3.88881893,
     43.60871606
  },
  {
     "34172_EUROPA",
     "Europa",
     "FR_MTP_EURO",
     3.89253074,
     43.60784971
  },
  {
     "34172_CORUM",
     "Corum",
     "FR_MTP_CORU",
     3.88225773,
     43.61388821
  },
  {
     "34172_SAINTRO",
     "Saint Roch",
     "FR_MTP_GARE",
     3.87855072,
     43.60329149
  },
  {
     "34057_DEGAUL",
     "Charles de Gaulle",
     "FR_CAS_CDGA",
     3.8977621,
     43.62854212
  },
  {
     "34172_LORCA",
     "Garcia Lorca",
     "FR_MTP_GARC",
     3.8907158,
     43.59098509
  },
  {
     "34172_SABINE",
     "Sabines",
     "FR_MTP_SABI",
     3.8602246,
     43.58383263
  },
  {
     "34172_MOSSON",
     "Mosson",
     "FR_MTP_MOSS",
     3.81966554,
     43.61623716
  },
  {
     "34172_EUROME",
     "Euromédecine",
     "FR_MTP_MEDC",
     3.82772365,
     43.63895359
  },
  {
     "34172_OCCITA",
     "Occitanie",
     "FR_MTP_OCCI",
     3.84859796,
     43.63456232
  },
  {
     "34270_LESEC",
     "Saint-Jean-le-Sec",
     "FR_STJ_SJLC",
     3.8379312,
     43.57082225
  }
};

float distance(float x1, float y1, float x2, float y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}




char * parseParckXML (char * source,char * tagStart,char * tagClose){
	char *target = NULL;
    char *start, *end;

    if ( start = strstr( source, tagStart ) )
    {
        start += strlen( tagStart );
        if ( end = strstr( start, tagClose ) )
        {
            target = ( char * )malloc( end - start + 1 );
            memcpy( target, start, end - start );
            target[end - start] = '\0';
        }
    }
	return target;
}

void main()
{
	 float X = 43.5;
	 float Y = 3.6;
	 float max_distance = 0.25;
	 
	 //char * xml = "<park><DateTime>2021-12-13T11:59:51</DateTime><Name>ARCT</Name><Status>Open</Status><Free>0093</Free><Total>0440</Total></park>"
	 
	 
	 //printf("%s \n",_getXmlValue(xml,"DateTime"));
	 
	 /*int i = 0;
      int selectedIndexArray [22];
      int selecetdArraySize = 0;
      int N = sizeof(data) / sizeof(Parck);
      for(i;i<N;i++){
        if(distance(X,Y,data[i].lon,data[i].lat) <= max_distance){
          selectedIndexArray[selecetdArraySize] = i;
          selecetdArraySize++;
          
          }
        }
        
        for(i =0;i<selecetdArraySize;i++){
		
	printf("%d-%s \n",i,data[i].name);
		
	}*/
	
	int i = 0;
	int N = sizeof(data) / sizeof(Parck);
	for(i;i<N;i++){
		//if(distance(X,Y,data[i].lon,data[i].lat) <= max_distance){
			printf("%d-%f \n",i,distance(X,Y,data[i].lon,data[i].lat));
		//}
	
		
	}
	
	/* XML source, could be read from disk
	 */
/*	uint8_t* source = ""
		"<Root>"
			"<Hello>World</Hello>"
			"<This>"
				"<Is>:-)</Is>"
				"<An>:-O</An>"
				"<Example>:-D</Example>"
			"</This>"
		"</Root>"
	;*/
	
	/*char * source = "<park><DateTime>2021-12-13T11:59:51</DateTime><Name>ARCT</Name><Status>Open</Status><Free>0093</Free><Total>0440</Total></park>";
	
	char * date = parseParckXML (source,"<DateTime>","</DateTime>");
	char * status = parseParckXML (source,"<Status>","</Status>");
	char * totel = parseParckXML (source,"<Total>","</Total>");
	
	printf("%s**%s**%s",date,status,totel);
	free(date);
	free(status);
	free(totel);
	//printf("%d* \n",  atoi(parckXML.total));*/




	





	
}

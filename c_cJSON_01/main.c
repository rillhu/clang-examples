#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#define STA_SIZE			(16)

typedef struct
{
	int day;
	int night;
	int min;
	int max;
	int morn;
	int eve;

}xTemperature_t;

typedef struct
{
	int id;
	char wmain[STA_SIZE];
	char wdes[STA_SIZE];
	char wicon[STA_SIZE];
}xWeather_t;

typedef struct
{
	int dt;					/* 当前时间 */
	int pressure;
	int humidity;
	int speed;
	int deg;
	int clouds;
	xTemperature_t temperature;
	xWeather_t weather;
}xWeatherList_t;

xWeatherList_t weather[3];
xWeatherList_t *weatherList = &weather[0];

static void weather_json_parse(const char *jsStr)
{
    int cpySiz=0;
    cJSON *jsTmp=NULL; //temp var
    cJSON *jsonRoot=cJSON_Parse(jsStr);
    cJSON *jsWeatherRoot=NULL;
    cJSON *jsWeatherList=NULL;
    cJSON *jsTemp=NULL;
    cJSON *jsWeather=NULL;
    printf("Start jSON\n");

    if(!jsonRoot){
        printf("Error before: %s\n",cJSON_GetErrorPtr());
    }else{

        jsWeatherRoot   = cJSON_GetObjectItem(jsonRoot, "list");
        jsWeatherList   = cJSON_GetArrayItem(jsWeatherRoot,0); //The current day data

        jsTemp          = cJSON_GetArrayItem(jsWeatherList,1); //Temperature data
        jsTmp           = cJSON_GetArrayItem(jsWeatherList,4); //Weather data

        jsWeather       = cJSON_GetArrayItem(jsTmp,0);         //Weather

        printf("Start jSON2\n");
       	/*---------------------------------------------------------------------*/
    	weatherList->dt         = cJSON_GetArrayItem(jsWeatherList,0)->valueint; //Time UTC
    	weatherList->pressure   = cJSON_GetArrayItem(jsWeatherList,2)->valueint; //Pressure
    	weatherList->humidity   = cJSON_GetArrayItem(jsWeatherList,3)->valueint; //humidity
    	weatherList->speed      = cJSON_GetArrayItem(jsWeatherList,5)->valueint; //Weather
    	weatherList->deg        = cJSON_GetArrayItem(jsWeatherList,6)->valueint; //Wind speed
    	weatherList->clouds     = cJSON_GetArrayItem(jsWeatherList,7)->valueint; //Clouds

       	/*-------------------------Weather data--------------------------------*/
        weatherList->weather.id = cJSON_GetObjectItem(jsWeather,"id")->valueint;
        cpySiz=strlen(cJSON_GetObjectItem(jsWeather,"main")->valuestring);
        if (cpySiz>STA_SIZE)
        	cpySiz=STA_SIZE;
        strcpy(weatherList->weather.wmain,cJSON_GetObjectItem(jsWeather,"main")->valuestring);

        cpySiz=strlen(cJSON_GetObjectItem(jsWeather,"description")->valuestring);
        if (cpySiz>STA_SIZE)
        	cpySiz=STA_SIZE;
        strcpy(weatherList->weather.wdes,cJSON_GetObjectItem(jsWeather,"description")->valuestring);

        cpySiz=strlen(cJSON_GetObjectItem(jsWeather,"icon")->valuestring);
        if (cpySiz>STA_SIZE)
        	cpySiz=STA_SIZE;
        strcpy(weatherList->weather.wicon,cJSON_GetObjectItem(jsWeather,"icon")->valuestring);

       	/*--------------------------Temperature data----------------------------*/
        weatherList->temperature.day=cJSON_GetObjectItem(jsTemp,"day")->valueint;
        weatherList->temperature.night=cJSON_GetObjectItem(jsTemp,"night")->valueint;
        weatherList->temperature.min=cJSON_GetObjectItem(jsTemp,"min")->valueint;
        weatherList->temperature.max=cJSON_GetObjectItem(jsTemp,"max")->valueint;
        weatherList->temperature.morn=cJSON_GetObjectItem(jsTemp,"morn")->valueint;
        weatherList->temperature.eve=cJSON_GetObjectItem(jsTemp,"eve")->valueint;
        printf("Weather: %s,Temp:%d\n",weatherList->weather.wmain, weatherList->temperature.day);        
/*
        cJSON_Delete(jsWeatherRoot);
        cJSON_Delete(jsWeatherList);
        cJSON_Delete(jsWeather);
        cJSON_Delete(jsTemp);
*/
        cJSON_Delete(jsonRoot);


    }
}
// 被解析的JSON数据包
char pbuf[] = "{\"city\":{\"id\":1790630,\"name\":\"Xian\",\"coord\":{\"lon\":108.9286,\"lat\":34.2583},\"country\":\"CN\",\"population\":0},\"cod\":\"200\",\"message\":0.0522146,\"cnt\":1,\"list\":[{\"dt\":1493697600,\"temp\":{\"day\":20.22,\"min\":13.59,\"max\":20.22,\"night\":13.59,\"eve\":17.98,\"morn\":20.22},\"pressure\":932.91,\"humidity\":58,\"weather\":[{\"id\":501,\"main\":\"Rain\",\"description\":\"moderate rain\",\"icon\":\"10d\"}],\"speed\":3.67,\"deg\":144,\"clouds\":92,\"rain\":11.48}]}";
int main (int argc, const char * argv[])
{
	/*使用cJSON解析，JSAON数据格式*/ 
	weather_json_parse(pbuf);
	

	/*使用cJSON生成JSON数据格式*/ 
	cJSON *root, *datastreams, *datastream,*datapoints,*datapoint;
	char *out;
	
	root = cJSON_CreateObject(); // 创建根root
	//cJSON_AddNumberToObject(root, "total", 3);
	
	// 在object root中加入array datastreams
	cJSON_AddItemToObject(root, "datastreams", datastreams = cJSON_CreateArray());

	// 在array datastreams中加入object datastream
	cJSON_AddItemToArray(datastreams, datastream = cJSON_CreateObject());	
	//在object datastream中加入节点（键值对），节点名：id，节点值： Temperature
	cJSON_AddItemToObject(datastream, "id", cJSON_CreateString("Temperature"));
	
	// 在object datastream中加入array datapoints
	cJSON_AddItemToObject(datastream, "datapoints",datapoints = cJSON_CreateArray());
	// 在array datapoints中加入object datapoint
	cJSON_AddItemToArray(datapoints, datapoint = cJSON_CreateObject());
	//在object datapoint中加入节点（键值对），节点名：at，节点值： 2017-05-09	
	cJSON_AddItemToObject(datapoint, "at", cJSON_CreateString("2017-05-09"));
	//在object datapoint中加入节点（键值对），节点名：value，节点值：23.5	
	cJSON_AddItemToObject(datapoint,"value", cJSON_CreateNumber(23.5));
	
	// 在array datastreams中加入object datastream
	cJSON_AddItemToArray(datastreams, datastream = cJSON_CreateObject());	
	//在object datastream中加入节点（键值对），节点名：id，节点值： Temperature
	cJSON_AddItemToObject(datastream, "id", cJSON_CreateString("location"));
	
	// 在object datastream中加入array datapoints
	cJSON_AddItemToObject(datastream, "datapoints",datapoints = cJSON_CreateArray());
	// 在array datapoints中加入object datapoint
	cJSON_AddItemToArray(datapoints, datapoint = cJSON_CreateObject());
	//在object datapoint中加入节点（键值对），节点名：at，节点值： 2017-05-09	
	cJSON_AddItemToObject(datapoint, "longitude", cJSON_CreateNumber(108.3333));
	//在object datapoint中加入节点（键值对），节点名：value，节点值：23.5	
	cJSON_AddItemToObject(datapoint,"latitude", cJSON_CreateNumber(35.5111));

	// 打印并释放
	out = cJSON_Print(root); 
	printf("%s\n",out);
	printf("%d\n",strlen(out));
	cJSON_Delete(root); printf("%s\n",out); free(out);
	
	/*生成的JSON数据格式 
	{
	        "datastreams":  [
					{ //stream 1
	                        "id":   "Temperature",
	                        "datapoints":   [{
	                                        "at":   "2017-05-09",
	                                        "value":        23.500000
	                                }]
	                }, 
					{//stream 2
	                        "id":   "location",
	                        "datapoints":   [{
	                                        "longitude":    108.333300,
	                                        "latitude":     35.511100
	                                }]
	                }]
	}
	*/

	root = cJSON_CreateObject(); // Create rootobject
	//cJSON_AddNumberToObject(root, "total", 3);

	//Add array (datastream) into object (root).
	cJSON_AddItemToObject(root, "datastreams", datastreams = cJSON_CreateArray());

    //stream 1
	// Add object (datastream) into array (datastreams)
	cJSON_AddItemToArray(datastreams, datastream = cJSON_CreateObject());
	//Add item (key:val) into object (datastream), key:id, val: Temperature
	cJSON_AddItemToObject(datastream, "id", cJSON_CreateString("TempHumi"));
	// Add array (datapoints) into object (datastream).
	cJSON_AddItemToObject(datastream, "datapoints",datapoints = cJSON_CreateArray());
	// Add object (datapoint) into array (datapoints)
	cJSON_AddItemToArray(datapoints, datapoint = cJSON_CreateObject());
	//Add item (key:val) into object (datapoint), key:at, val: 2017-05-09 10:15:00
	cJSON_AddItemToObject(datapoint, "Temperature", cJSON_CreateNumber(28));
	//Add item (key:val) into object (datapoint), key:value, val: cJSON_CreateNumber(23.5)
	cJSON_AddItemToObject(datapoint,"Humidity", cJSON_CreateNumber(16));

    //stream 2
	// Add object (datastream) into array (datastreams)
	cJSON_AddItemToArray(datastreams, datastream = cJSON_CreateObject());
	//Add item (key:val) into object (datastream), key:id, val: location
	cJSON_AddItemToObject(datastream, "id", cJSON_CreateString("GPS"));
	// Add array (datapoints) into object (datastream).
	cJSON_AddItemToObject(datastream, "datapoints",datapoints = cJSON_CreateArray());
	// Add object (datapoint) into array (datapoints)
	cJSON_AddItemToArray(datapoints, datapoint = cJSON_CreateObject());
	//Add item (key:val) into object (datapoint), key:longitude, val: cJSON_CreateNumber(108.3333)
	cJSON_AddItemToObject(datapoint, "Longitude", cJSON_CreateNumber(108.3333));
	//Add item (key:val) into object (datapoint), key:latitude, val: cJSON_CreateNumber(35.5111)
	cJSON_AddItemToObject(datapoint,"Latitude", cJSON_CreateNumber(35.5111));
	// 打印并释放
	out = cJSON_Print(root); 	
	printf("%d\n",strlen(out));
	cJSON_Delete(root); printf("%s\n",out); free(out);	
	
	/*生成JSON数据格式如下： 
		
		{
	        "datastreams":  [{
	                        "id":   "TempHumi",
	                        "datapoints":   [{
	                                        "Temperature":  28,
	                                        "Humidity":     16
	                                }]
	                }, {
	                        "id":   "GPS",
	                        "datapoints":   [{
	                                        "Longitude":    108.333300,
	                                        "Latitude":     35.511100
	                                }]
	                }]
		}
	*/

}






all: Freak
ColorHist:
	#g++ -o ColorHist -l opencv_legacy ColorHist.cpp 
	#g++ -o ColorHist -I /usr/local/Cellar/opencv/2.4.2/include/opencv/ ColorHist.cpp 
	#g++ ColorHist.cpp -o ColorHist -I /usr/local/Cellar/opencv/2.4.2/include/opencv/ -L /usr/local/Cellar/opencv/2.4.2/lib -lopencv_highgui -lopencv_legacy -lopencv_core -lopencv_contrib -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_imgproc -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_ts -lopencv_video -lopencv_videostab
	#-lopencv_highgui -lopencv_calib3d -lopencv_legacy -lopencv_core
	# -lopencv_contrib -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_imgproc -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_ts -lopencv_video -lopencv_videostab
	g++ ColorHist.cpp -o ColorHist -I /usr/local/Cellar/opencv/2.4.2/include/ -L /usr/local/Cellar/opencv/2.4.2/lib -lopencv_highgui -lopencv_legacy -lopencv_core -lopencv_contrib -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_imgproc -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_ts -lopencv_video -lopencv_videostab
Freak:
	g++ Freak.cpp KMinHeap.cpp mysql_header.h -o Freak -I /usr/local/Cellar/opencv/2.4.2/include/ -L /usr/local/Cellar/opencv/2.4.2/lib -lopencv_highgui -lopencv_legacy -lopencv_core -lopencv_contrib -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_imgproc -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_ts -lopencv_video -lopencv_videostab -I/usr/local/include -I/usr/local/include/cppconn -l mysqlcppconn
Linux:
	g++ Freak.cpp KMinHeap.cpp mysql_header.h /usr/lib/libmysqlcppconn.so -o Freak -I /usr/include/OpenCV-2.4.2/include -L /usr/include/OpenCV-2.4.2/lib -lopencv_highgui -lopencv_legacy -lopencv_core -lopencv_contrib -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_imgproc -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_ts -lopencv_video -lopencv_videostab -I/usr/include -I/usr/include/ -l mysqlcppconn
clean:
	rm Freak
redo:
	make clean
	make
	

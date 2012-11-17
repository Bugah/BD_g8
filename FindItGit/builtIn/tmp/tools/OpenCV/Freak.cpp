#include <iostream>
#include <string>
#include <vector>
/*
#include "/usr/include/OpenCV-2.4.2/modules/core/include/opencv2/core/core.hpp"
#include "/usr/include/OpenCV-2.4.2/modules/highgui/include/opencv2/highgui/highgui.hpp"
#include "/usr/include/OpenCV-2.4.2/modules/features2d/include/opencv2/features2d/features2d.hpp"
#include "/usr/include/OpenCV-2.4.2/modules/legacy/include/opencv2/legacy/legacy.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/legacy/legacy.hpp>
*/

#include <OpenCV-2.4.2/modules/core/include/opencv2/core/core.hpp>
#include <OpenCV-2.4.2/modules/highgui/include/opencv2/highgui/highgui.hpp>
#include <OpenCV-2.4.2/modules/features2d/include/opencv2/features2d/features2d.hpp>
#include <OpenCV-2.4.2/modules/legacy/include/opencv2/legacy/legacy.hpp>

#include "KMinHeap.h"
#include "mysql_header.h"
#include <cppconn/exception.h>

using namespace cv;

using namespace sql::mysql;

using namespace std;


int ratioTest(vector < vector < DMatch > > matches, float ratio);
void symmetryTest(
           const vector < vector < DMatch > > matches1,
           const vector < vector < DMatch > > matches2,
           std::vector<cv::DMatch> symMatches);

int main( int argc, char** argv ) {
    /* Variaveis de Busca */
    string command="SELECT * FROM TABIMG";
    int counter;
    const char *imagepath;
    string ImagePath;
    KMinHeap Heapzim;
    int indice_bd;

    /* Variaveis de Conexao */
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;


    /* Conecta com o DB */
    driver =sql::mysql::get_driver_instance();
    con = driver->connect(DBHOST, USER, PASSWORD);
    con->setSchema(DATABASE);
    /* Fim da coneccao ao schema definido no header */
    
    // Load #1 image
    Mat imgA = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE );
    if( !imgA.data ) {
        std::cout<< " --(!) Error reading image " << argv[1] << std::endl;
        return -1;
    }
    // End Load #1 Image
    
    // DETECTION
    SurfFeatureDetector detector(2000,4);
    FastFeatureDetector detector2(2000,4);
    
    // DESCRIPTOR
    cv::FREAK extractor;

    BruteForceMatcher<Hamming> matcher;
    
    std::vector<KeyPoint> keypointsA; //keypointsB;
    Mat descriptorsA;   //descriptorsB;
    //std::vector<DMatch> matches;
    
    // detect
    detector.detect( imgA, keypointsA );
    
    // extract
    extractor.compute( imgA, keypointsA, descriptorsA );
    
    /* Numero de Keypoints */
    
    double keyA;
    keyA=keypointsA.size();
    
    
    
    // Busca todos termos no BD
    pstmt = con->prepareStatement(command);
    res = pstmt->executeQuery();
    
    
    while (res->next()) {
        indice_bd=res->getInt("Id");
        
        ImagePath.clear();
        ImagePath.append("jpgFiles/");
        ImagePath.append(res->getString("Nome"));
        ImagePath.append(".jpg");
        
        imagepath=ImagePath.c_str();
        Mat imgB;
        //cout << "indice_bd" << indice_bd << endl;
        //if(indice_bd>=3496)
        imgB = imread(imagepath, CV_LOAD_IMAGE_GRAYSCALE );
        if(( !imgB.data )||(indice_bd==1009)||(indice_bd==1316)||(indice_bd==1698)||(indice_bd==2652)||(indice_bd==2792)||(indice_bd==2859)||(indice_bd==2930)||(indice_bd==3448)||(indice_bd==3447)||(indice_bd==3497)) {
                //std::cout << " --(!) Error reading image " << imagepath << std::endl;
                //return -1;
        }
        else {
        // Variaveis do ponto B
        std::vector<KeyPoint> keypointsB;
        Mat descriptorsB;
        
        std::vector<DMatch> matches;
        //vector < vector < DMatch > > matches;
        
        //std::vector<DMatch> matches_b;
        //vector < vector < DMatch > > matches_b;
        
        // detector/extractor B
        detector.detect( imgB, keypointsB );
        extractor.compute( imgB, keypointsB, descriptorsB );
        // match A B
        
        double keyB;
        keyB=keypointsB.size();
        
        
        matcher.match(descriptorsA, descriptorsB, matches);
        //matcher.knnMatch(descriptorsA, descriptorsB, matches,2);
        //matcher.knnMatch(descriptorsB, descriptorsA, matches_b,2);
        
        /*
        cout << "Matches.size(): " << matches.size() << " Matches[0].size(): " << matches[0].size() << endl;
        //cout << "Matches_b.size(): " << matches_b.size() << endl;
        
        int removed=0;
        int m=0,n;
        int ratio=20;
        //removed = ratioTest(matches, 10);
        
        while(m<matches.size()) {
            if(matches[m].size()==2) {
                //cout << "matches[m][0].distance: " << matches[m][0].distance << " matches[m][1].distance: " << matches[m][1].distance << endl;
                
                if(matches[m][1].distance - matches[m][0].distance <= ratio ) {
                    //cout << "Eliminei!" << endl;
                    matches.erase(matches.begin()+m);
                    removed=removed+1;
                }
                else {
                    m=m+1;
                }
            }
            else {
                matches.erase(matches.begin()+m);
                removed=removed+1;
            }
        }
        
        cout << "Removed: " << removed << endl;
        cout << "Matches.size(): " << matches.size() << endl;
        //cout << "Matches_b.size(): " << matches_b.size() << endl;
        */
        
        //std::vector<cv::DMatch> symMatches;
        
        //symmetryTest(matches,matches_b,symMatches);
        
        // Conta aqueles <=100
        int i;
        double lower100=0;
        double auxiliar;
        double total_key=keyA+keyB;
        //int lower90=0;
        //int lower80=0;
        //int lower70=0;

        for(i=0; i<matches.size(); i=i+1) {
            //std::cout << "Distance : " << matches[i][0].distance << std::endl;
            if(matches[i].distance<=100) {
                if(matches[i].distance!=0) {
                    auxiliar=(1/matches[i].distance);
                    auxiliar=auxiliar*auxiliar;
                    auxiliar=auxiliar*auxiliar;
                    lower100=lower100+auxiliar;
                    //lower100=lower100+(1/matches[i].distance);
                }
                else 
                        lower100=lower100+2;
            }
        
            
            //if(matches[i].distance<=60)
            //    lower100=lower100+1;
            /*if(matches[i].distance<=90)
                lower90=lower90+1;
            if(matches[i].distance<=80)
                lower80=lower80+1;
            if(matches[i].distance<=70)
                lower70=lower70+1;*/
        }
        
        //lower100=lower100*lower100;
        //lower100=lower100/matches.size();
        lower100=1000000000*lower100;
        lower100=lower100/total_key;
        
        
        //cout << "Id : " << indice_bd << " Lower100: " << lower100 << endl;
        Heapzim.Attempt(lower100, indice_bd);
        //Heapzim.PrintHashDebug();
        
        counter = counter + 1;
        if(counter%200==0) {
            //cout << "Counter : " << counter << endl;
            Heapzim.PrintHashDebug();
        }
        }
                    
    } 
    
    
    Heapzim.OrderHash();
    Heapzim.PrintHash();
    //Heapzim.PrintHashDebug();

    
    // Draw matches
    /*Mat imgMatch;
    drawMatches(imgA, keypointsA, imgB, keypointsB, matches, imgMatch);

    namedWindow("matches", CV_WINDOW_KEEPRATIO);
    imshow("matches", imgMatch); 
    
    waitKey(0); */
}




int ratioTest(vector < vector < DMatch > > matches, float ratio) {
    
    int removed=0;
    // for all matches         for (std::vector<std::vector<cv::D

    for (vector < vector < DMatch > >::iterator matchIterator = matches.begin(); matchIterator!= matches.end(); ++matchIterator) {

        // if 2 NN has been identified
        if (matchIterator->size() > 1) {
        // check distance ratio
                //if ((*matchIterator)[0].distance/ (*matchIterator)[1].distance < ratio) {
                if ((*matchIterator)[0].distance - (*matchIterator)[1].distance > ratio) {
                        matchIterator->clear(); // remove match
                        removed++; 
                }
        } 
        else { // does not have 2 neighbours
                matchIterator->clear(); // remove match
                removed++; 
        }
    }
    
    return removed;
} 



// Insert symmetrical matches in symMatches vector
void symmetryTest(
           const vector < vector < DMatch > > matches1,
           const vector < vector < DMatch > > matches2,
           std::vector<cv::DMatch> symMatches) {
    
    // for all matches image 1 -> image 2
    
    for (vector < vector < DMatch > >::const_iterator matchIterator1= matches1.begin(); matchIterator1!= matches1.end(); ++matchIterator1) {
            
        // ignore deleted matches
            if (matchIterator1->size() < 2)
                continue;
            
            // for all matches image 2 -> image 1
            for (vector < vector < DMatch > >:: const_iterator matchIterator2= matches2.begin(); matchIterator2!= matches2.end(); ++matchIterator2) {
               
                // ignore deleted matches
               if (matchIterator2->size() < 2)
                        continue;
               
               // Match symmetry test
               if ((*matchIterator1)[0].queryIdx ==
                   (*matchIterator2)[0].trainIdx  &&
                   (*matchIterator2)[0].queryIdx ==
                   (*matchIterator1)[0].trainIdx) {
                   // add symmetrical match
                     symMatches.push_back(

  cv::DMatch((*matchIterator1)[0].queryIdx,
            (*matchIterator1)[0].trainIdx,
            (*matchIterator1)[0].distance));
break; // next match in image 1 -> image 2

               }
            }
    }
}

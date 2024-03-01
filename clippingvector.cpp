#pragma once
#include "clipper.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <ReadINSL.h>
#include <IntechHMIutil.h>
#include <IntechReadINSL.h>
#include <IntechMemoryManagement.h>
#include <INSLReaderFactory.h>
#include <IntechAPI.h>
#include <IntechHMIstruct.h>
#include <IntechHMIutil.h>
#include <IntechReadINSL.h>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

//copy project
using namespace cv;
using namespace std;
#define PRECISION 10000 

//struct Point_2D {
//public:
//    double _x = 0.0;
//    double _y = 0.0;
//
//    void Serialize(std::ofstream& writeObject) {
//        try {
//            int _val = (int)(this->_x * PRECISION);
//            writeObject.write(reinterpret_cast<const char*>(&_val), sizeof(int));
//            _val = (int)(this->_y * PRECISION);
//            writeObject.write(reinterpret_cast<const char*>(&_val), sizeof(int));
//        }
//        catch (std::exception&) {
//        }
//    }
//    void Deserialize(std::ifstream& readObject) {
//        try {
//            int _val;
//            readObject.read((char*)(&_val), sizeof(int));
//            this->_x = ((double)_val / PRECISION);
//            readObject.read((char*)(&_val), sizeof(int));
//            this->_y = ((double)_val / PRECISION);
//        }
//        catch (std::exception&) {
//        }
//    }
//};

//Contour datatype
typedef std::vector<Point_2D> polyline;
typedef std::vector<polyline> Contour;




// Function prototypes
Point2f pixelToRealCoordinates(int pixelX, int pixelY, int sidelength, int baseplatesize);
Contour DrawOnWhitePixelContour(Mat& image, Mat& binary, const std::vector<ContourInfo>& _contourinfo, int sideLength, int baseplatesize);
Mat perspectiveTransform(const Mat& originalImage, const vector<Point2f>& source_points, int sideLength);
void colorShape(Mat& image, const vector<Point2f>& contourPoints, int sideLength, int baseplate);
Point2f convertcordinates(float x, float y, int sidelenght, int baseplate);
vector<Point2f> getPointsInsidePolygon(const vector<Point2f> contourPoints, int sideLength, int baseplate);
void ConvertContourInfoToContour(const std::vector<ContourInfo>& _contourinfo, Contour& _in);
ClipperLib::Paths UnionofContourHatches(Contour& _in, ClipperLib::Paths Hatches);
void DrawClippedVector(cv::Mat& image, const ClipperLib::Paths& clippedVector, double scale, int sideLength, int baseplatesize);
ClipperLib::Paths ClipVectorWithContour(const Contour& contour, const ClipperLib::Path& vector);
ClipperLib::Paths ConvertContourToClipperPaths(const Contour& contour);
//ClipperLib::Paths clipvectorwithcontour(const Contour& _in, const ClipperLib::Path& vector);

// Main function
int main() {

    //Mat src = imread("C:\\Users\\kunal.g\\Pictures\\buildlayer\\LayerNumber1940.png");;

    //namedWindow("src", WINDOW_AUTOSIZE);
    //imshow("src", src);

    //Mat someGradientMat(src.size(), CV_8U, Scalar(0));

    //int limit = src.size().height;

    //double a = -255.0 * 4.0 / (limit * limit);
    //double b = 255.0 * 4.0 / limit;
    //double c = 0;

    //for (int r = 0; r < limit; r++) {

    //    //value is the parabole y = ax^2 + b + c
    //    int value = (int)(a * r * r + b * r + c);

    //    someGradientMat.row(r).setTo(value);
    //}
    //namedWindow("someGradientMat", WINDOW_NORMAL);
    //imshow("someGradientMat", someGradientMat);

    //Mat dst;
    //compare(src, someGradientMat, dst, CMP_LT);

    //namedWindow("dst", WINDOW_NORMAL);
    //imshow("dst", dst);

    //waitKey(0);


    //Mat src = imread("C:\\Users\\kunal.g\\Pictures\\buildlayer\\LayerNumber1940.png");

    //namedWindow("src", WINDOW_AUTOSIZE);
    //imshow("src", src);

    //Mat someGradientMat(src.size(), CV_8U, Scalar(0));

    //int limit = src.size().height;

    //double a = -255.0 * 4.0 / (limit * limit);
    //double b = 255.0 * 4.0 / limit;
    //double c = 0;

    //for (int r = 0; r < limit; r++) {
    //    // Value is the parabola y = ax^2 + bx + c
    //    int value = static_cast<int>(a * r * r + b * r + c);
    //    someGradientMat.row(r).setTo(value);
    //}

    //namedWindow("someGradientMat", WINDOW_NORMAL);
    //imshow("someGradientMat", someGradientMat);

    //// Convert src to grayscale
    //Mat srcGray;
    //cvtColor(src, srcGray, COLOR_BGR2GRAY);

    //Mat dst;
    //compare(srcGray, someGradientMat, dst, CMP_LT);

    //namedWindow("dst", WINDOW_NORMAL);
    //imshow("dst", dst);

    //waitKey(0);



    //std::ifstream file("C:\\Users\\kunal.g\\source\\repos\\DEFECT_DETECTION\\3dpd_set1_alsi10mg_40mic_26102023.insl"); // Open file in read mode and set the position to the end

    //if (!file.is_open()) {
    //    std::cerr << "Failed to open the file." << std::endl;
    //    return 1;
    //}

    //// Check if the file is empty
    //if (file.tellg() == 0) {
    //    std::cout << "The file is empty." << std::endl;
    //}
    //else {
    //    std::cout << "The file is not empty." << std::endl;
    //}

    //ClipperLib::Clipper clipper;
    // ENTER THE INSL FILE
    const std::string filePath = "C:\\Users\\kunal.g\\source\\repos\\DEFECT_DETECTION\\3dpd_set1_alsi10mg_40mic_26102023.insl";
    //3dpd_set1_alsi10mg_40mic_26102023
    //AlSi10Mg_40mic_uniform
    // 10layerINSL
    // CubeINSL
    //SampleBlockFinRev

    // Load the image
    Mat originalImage = imread("C:\\Users\\kunal.g\\Pictures\\buildlayer\\LayerNumber1940.png");
    int layer;
    cout << "enter layer" << endl;
    cin >> layer;

    std::ifstream ff;
    ff.open(filePath, std::ios::in | std::ios::binary);

    if (!ff.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }
    else {
        cout << "file opened" << std::endl;
    }
    //ff.seekg(0, std::ios::beg);

    INSLMemoryManagementClass memoryobj;
    INSLversion_020 obj;
    obj.readHeader(ff);

    obj.INSLversion_020::ReadFile(memoryobj, ff, layer);
    const std::vector<ContourInfo> _contourinfo = memoryobj.INSLMemoryManagementClass::GetContourInfo();
    cout << "Number of contours" << _contourinfo.size() << endl;


     //layer info
    const std::vector<HatchInfo> _hatchinfo = memoryobj.INSLMemoryManagementClass::GetHatchInfo();
    cout << "Number of hatches *2 " << _hatchinfo.size();
        
    
        /* const double precision  = 1000.0;
         ClipperLib::Paths PathsInsideContour;
         for (int i = 0; i < _hatchinfo.size() / 2; i++) {
              PathsInsideContour = ClipPathAgainstContours(_contourinfo, startPoints[i], endPoints[i], precision);
         }

         for (int i = 0; i < PathsInsideContour.size(); i++) {
             cout << " the path is " << endl;
             cout<< "start point" << PathsInsideContour[i][0].X <<endl;
             cout << "end point" << PathsInsideContour[i][1].Y << endl;
         }*/



         //commented here

        if (originalImage.empty()) {
            cerr << "Error: Couldn't read the image" << endl;
            return -1;
        }

        // Define the source points (corner points of the distorted rectangle)
        vector<Point2f> source_points = {
            Point2f(409, 232), // top-left corner
            Point2f(981, 196), // top-right corner
            Point2f(1015, 807), // bottom-right corner
            Point2f(412, 809)  // bottom-left corner
        };


        int baseplatesize = 325; //mm
        int sideLength = 1000; // pixel

        // Perform the perspective transformation
        Mat correctedImage = perspectiveTransform(originalImage, source_points, sideLength);
        // Convert to grayscale and threshold
        Mat gray, binary;
        cvtColor(correctedImage, gray, COLOR_BGR2GRAY);   // to grey
        double lowval = 150;     // threshold value
       threshold(gray, binary, lowval, 255, THRESH_BINARY);
       // adaptiveThreshold(gray, binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, 1);
       
       // int blockSize = 2; // Increased block size
       // int C = 1; // Reduced C value

        // Experiment with using ADAPTIVE_THRESH_GAUSSIAN_C
       // adaptiveThreshold(gray, binary, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, blockSize, C);
        // Find contours and draw them

       
       //printing insl contour
        for (int i = 0; i < _contourinfo.size(); i++) {
            //const std::vector<Point2f> contourpoints = _contourinfo[i].contourpoints;
          //  colorShape(correctedImage, contourpoints ,sideLength,baseplatesize);
           // cout << "contourpoints size of contour i = " << i << " is " << contourpoints.size() << endl;
        }


       // std::vector<Point2f> startPoints;
       // std::vector<Point2f> endPoints;
        

        Contour defectcontour = DrawOnWhitePixelContour(correctedImage, binary, _contourinfo, sideLength, baseplatesize);
       

        int j = 0;
        for (int i = 0; i < _hatchinfo.size(); i++) {
            ClipperLib::Path hatch;
            for (const auto& point : _hatchinfo[i].hatchpoints) {
                if (j % 2 == 0) {
                    
                    long long  x = point.x * PRECISION;
                    long long  y = point.y * PRECISION;

                    ClipperLib::IntPoint startpoint(x, y);
                    hatch.push_back(startpoint);

                    Point2f convertpt1 = convertcordinates(point.x,point.y, sideLength, baseplatesize);
                   // cout << "hatch start pt" << point.x << " " << point.y << endl;
                    //cv::circle(correctedImage, convertpt1, 1, cv::Scalar(255, 0, 0), -1);
                    // cout << "start point" << endl;
                     //std::cout << "X: " << point.x << ", Y: " << point.y << std::endl;
                    j++;
                    /*cv::Point2f convertedpoint = convertcordinates(point.x, point.y, sideLength, baseplatesize);
                    startPoints.push_back(convertedpoint);*/
                }
                else {

                    long long  x = point.x * PRECISION;
                    long long  y = point.y * PRECISION;

                    ClipperLib::IntPoint endpoint(x, y);
                    hatch.push_back(endpoint);
                    //cout << "hatch end pt" << point.x << " " << point.y << endl;
                    ClipperLib::Paths hatches;
                    hatches.push_back(hatch);
                   // ClipperLib::Paths clippedVector = clipvectorwithcontour(defectcontour, hatch);
                   // ClipperLib::Paths clippedVector111 = ClipVectorWithContour(defectcontour, hatch);
                    ClipperLib::Paths clippedVector = UnionofContourHatches(defectcontour, hatches);
                    /*if (clippedVector.size() > 0) {
                        cout << "not empty";
                    }*/
                    //draw hatch
                    
                    Point2f convertpt2 = convertcordinates(point.x , point.y, sideLength, baseplatesize);
                    // cv::line(image, convertpt1, convertpt2, cv::Scalar(255, 0, 0), 1); // Draw line in blue color
                    cv::Scalar color(0, 0, 0); // Green color
                    
                   // cv::circle(correctedImage, convertpt2, 1, cv::Scalar(255, 0, 0), -1);
                    DrawClippedVector(correctedImage, clippedVector, PRECISION ,sideLength,baseplatesize); // Adjust scale accordingly
                    hatch.clear();
                   // UnionofContourHatches(_in, hatches);
                    //cout << "end point" << endl;
                    //std::cout << "X: " << point.x << ", Y: " << point.y << std::endl;
                    j++;
                    // endPoints.push_back(point);
                }
                // cout<<typeid(point) .name()<<endl;

            }
        }












        //Contour _in;
        //ConvertContourInfoToContour(_contourinfo, _in);

        //convert defectcontour to _in data type and pass defectcontour instead of _in

        //ClipperLib::Paths ContourPath = UnionofContourHatches(_in, hatches);

        //int count = 0;
        //cv::Point2f startPoint;
        //cv::Point2f endPoint;
        //for (auto& Path : ContourPath)
        //{
        //    for (auto& pt : Path) {
        //        float x = pt.X ;
        //         x = x / 10000;
        //        float y = pt.Y ;
        //         y = y / 10000;
        //        cout << "clipped pts {" << x << "," << y <<"}" << endl;
        //        if (count % 2 == 0) {
        //            startPoint = { x, y };
        //            count++;
        //        }
        //         Define the starting and ending points of the vector
        //        else {
        //            count++;
        //            endPoint = { x,y };
        //             Define the color of the vector (BGR format)
        //            cv::Scalar color(0, 0, 0); // Green color
        //            Point2f sp = convertcordinates(startPoint.x, startPoint.y, sideLength, baseplatesize);
        //            Point2f ep = convertcordinates(endPoint.x, endPoint.y, sideLength, baseplatesize);
        //             Draw the vector on the image
        //            cv::line(correctedImage, sp, ep, color, 1); // 2 is the thickness of the line

        //            cv::circle(correctedImage, sp, 5, color, -1); // -1 fills the circle
        //            cv::circle(correctedImage, ep, 5, color, -1);

        //        }
        //    }
        //}

        // Display the result
        imshow("Detected Points", correctedImage);
        waitKey(0);
        imwrite("C:\\Users\\kunal.g\\source\\repos\\DEFECT_DETECTION\\resultimage.jpg", correctedImage);
        return 0;
    }


// Function definitions
//coloring the insl file area
void colorShape(Mat& image, const vector<Point2f>& contourPoints, int sideLength, int baseplate) {
    // Step 1: Transform the points
    vector<cv::Point> transformedPoints;

    for (const Point2f& pt : contourPoints) {
        Point transformed = convertcordinates(pt.x, pt.y, sideLength, baseplate);
        transformedPoints.emplace_back(transformed);
    }

    // Step 2 & 3: Draw and fill the polygon
    const cv::Point* pts = (const cv::Point*)Mat(transformedPoints).data;
    int npts = Mat(transformedPoints).rows;

    fillPoly(image, &pts, &npts, 1, Scalar(0, 255, 255)); // Yellow color
}

// Converts pixel to real-world coordinates
Point2f pixelToRealCoordinates(int pixelX, int pixelY, int sidelength, int baseplatesize) {
    const float scaleFactor = float(baseplatesize) / sidelength;
    float realX = pixelX * scaleFactor;
    float realY = (sidelength - pixelY) * scaleFactor;
    return Point2f(realX, realY);
}

//convert insl cordinate to cordinate compataible with opencv
Point2f convertcordinates(float x, float y, int sidelength, int baseplatesize) {
    // mm to pixel
    x = x * float(sidelength) / baseplatesize;
    y = y * float(sidelength) / baseplatesize;

    //baseplate center is at sidelength/2 ,sidelength/2
    x = x + float(sidelength) / 2 ;
    //y = y + sidelength/2;
    y = float(sidelength) / 2 - y;
    return Point2f(x, y);
}



//convert opencv cordinate to insl cordinate
Point2f convertCoordinatesToINSL(float x, float y, int sidelength, int baseplatesize) {
    // Revert the translation to move the origin back to the bottom-left
    x = x - float(sidelength) / 2;
    y = float(sidelength) / 2 - y;

    // Convert from pixels back to the original INSL units
    x = x * baseplatesize / float(sidelength);
    y = y * baseplatesize / float(sidelength);

    return Point2f(x, y);
}
//get points which are inside the contour
vector<Point2f> getPointsInsidePolygon(const vector<Point2f> contourPoints, int sideLength, int baseplate) {
    vector<Point2f> pointsInside;
    vector<Point> duplicate;
    for (const Point2f& p : contourPoints) {
        Point pp = convertcordinates(float(p.x), float(p.y), sideLength, baseplate);
        duplicate.emplace_back(pp);
    }

    Rect boundingBox = boundingRect(duplicate);
    cout << "duplicate.size()" << duplicate.size() << endl;
    cout << "Bounding Box: " << boundingBox << endl;
    for (int y = boundingBox.y; y <= boundingBox.y + boundingBox.height; y++) {
        for (int x = boundingBox.x; x <= boundingBox.x + boundingBox.width; x++) {
            Point pt = Point(x, y);
            if (pointPolygonTest(duplicate, Point2f(float(pt.x), float(pt.y)), false) >= 0) {
                pointsInside.emplace_back(Point2f(float(pt.x), float(pt.y)));
            }
        }
    }
    return pointsInside;
}

Contour DrawOnWhitePixelContour(Mat& image, Mat& binary, const std::vector<ContourInfo>& _contourinfo, int sideLength, int baseplatesize) {
    vector<vector<Point>> contours;
    findContours(binary, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    //for (size_t i = 0; i < contours.size(); i++) {
    //    // Draw the contour
    //    drawContours(image, contours, static_cast<int>(i), Scalar(0, 0, 255), 2);

    //    // Optionally, draw the centroid
    //    Moments m = moments(contours[i]);
    //    int cx = static_cast<int>(m.m10 / m.m00);
    //    int cy = static_cast<int>(m.m01 / m.m00);
    //   // circle(image, Point(cx, cy), 7, Scalar(255, 0, 0), -1);
    //}


    Contour defectcontour;
    for (size_t i = 0; i < contours.size(); i++) {
        polyline pl;
        for (size_t j = 0; j < contours[i].size(); j++) {
            // Convert each point using the provided conversion function
            Point2f convertedPoint = convertCoordinatesToINSL(contours[i][j].x, contours[i][j].y, sideLength, baseplatesize);

            Point_2D pt;
            pt.x = convertedPoint.x;
            pt.y = convertedPoint.y;
            pl.push_back(pt);
        }
        defectcontour.push_back(pl);
    }

   // polyline ans;
    for (const auto ci : _contourinfo) {

        vector<Point2f> inslPolygon = getPointsInsidePolygon(ci.contourpoints, sideLength, baseplatesize);
        //these two for loops too see points whihc are inside both defects and inslcontour
        for (const auto pt : inslPolygon) {
            //polyline dvec;
            for (const auto contour : contours) {
                Point2f newcord = Point2f(pt.x, pt.y);
                double ans = pointPolygonTest(contour, Point2f(float(newcord.x), float(newcord.y)), false);
                if (ans >= 0) {
                    // Draw the point in red color
                    image.at<Vec3b>(newcord.y, newcord.x) = Vec3b(0, 0, 255);
                   /* Point2f dcord = convertCoordinatesToINSL(newcord.x, newcord.y, sideLength, baseplatesize);
                    Point_2D polypt = { static_cast<double>(dcord.x),static_cast<double>(dcord.y) };
                    dvec.push_back(polypt);*/
                   // dvec.push_back(dcord);
                    //Convert to real-world coordinates
                    Point2f realCord = pixelToRealCoordinates(newcord.x, newcord.y, sideLength, baseplatesize);
                    cout << "Real world coordinates: (" << realCord.x << ", " << realCord.y << ")" << endl;
                    break;
                }
            }
            //defectcontour.push_back(dvec);
        }
    }
    return defectcontour;
}


// Performs the perspective transformation
//changing the resoloution of image the size of baseplate remain same
Mat perspectiveTransform(const Mat& originalImage, const vector<Point2f>& source_points, int sideLength) {
    // Define the destination points (corner points of the desired square)
    vector<Point2f> destination_points = {
        Point2f(0, 0),
        Point2f(sideLength, 0),
        Point2f(sideLength, sideLength),
        Point2f(0, sideLength)
    };

    // Compute the perspective transformation matrix
    Mat transformMatrix = getPerspectiveTransform(source_points, destination_points);

    // Apply the perspective transformation
    Mat correctedImage;
    warpPerspective(originalImage, correctedImage, transformMatrix, Size(sideLength, sideLength));
    return correctedImage;

}

//// Helper function to convert cv::Point2f to ClipperLib::IntPoint
//ClipperLib::IntPoint ConvertToPoint(cv::Point2f p, const double precision) {
//    return ClipperLib::IntPoint(static_cast<ClipperLib::cInt>(p.x * precision), static_cast<ClipperLib::cInt>(p.y * precision));
//}
//
//ClipperLib::Paths ClipPathAgainstContours(const std::vector<ContourInfo>& contours, const cv::Point_<float>& startPoint, const cv::Point_<float>& endPoint, const double precision = 1000.0) {
//    ClipperLib::Paths clipperContours;
//    ClipperLib::Path clipperPath;
//
//    // Convert ContourInfo contours to ClipperLib::Paths
//    for (const auto& contour : contours) {
//        ClipperLib::Path clipperContour;
//        for (const auto& pt : contour.contourpoints) {
//            clipperContour.push_back(ConvertToPoint(pt, precision));
//        }
//        clipperContours.push_back(clipperContour);
//    }
//
//    // Convert cv::Point path to ClipperLib::Path
//    clipperPath.push_back(ConvertToPoint(startPoint, precision));
//    clipperPath.push_back(ConvertToPoint(endPoint, precision));
//
//    // Clipping operation
//    ClipperLib::Clipper clipper;
//    clipper.AddPaths(clipperContours, ClipperLib::ptClip, true);
//    ClipperLib::Paths subject(1, clipperPath);
//    clipper.AddPaths(subject, ClipperLib::ptSubject, false);
//
//    ClipperLib::Paths result;
//    bool success = clipper.Execute(ClipperLib::ctIntersection, result, ClipperLib::pftEvenOdd, ClipperLib::pftEvenOdd);
//
//
//    // Check for successful clipping and non-empty result
//    if (success && !result.empty()) {
//        return result;
//    }
//    else {
//        // Handle the case when clipping did not produce a result
//        // You can return an empty Paths object or handle it as per your application logic
//        return ClipperLib::Paths();
//    }
//}
  
// Function to convert ContourInfo to Contour
void ConvertContourInfoToContour(const std::vector<ContourInfo>& _contourinfo, Contour& _in) {
    _in.clear(); // Clear existing contours in _in

    for (const auto& contourInfo : _contourinfo) {
        polyline pl;
        for (const auto& pt : contourInfo.contourpoints) {
            Point_2D point;
            point.x = static_cast<double>(pt.x);
            point.y = static_cast<double>(pt.y);
            pl.push_back(point);
        }
        _in.push_back(pl);
    }
}


//ClipperLib::Paths UnionofContourHatches(Contour& _in, const ClipperLib::Path& Hatches)
//{
//    try
//    {
//        ClipperLib::Paths _out{};
//        int _rSize = (int)_in.size();
//       
//        for (int _rIndex = 0; _rIndex < _rSize; ++_rIndex)
//        {
//            ClipperLib::Path _polyline{};
//            int _cSize = (int)_in[_rIndex].size();
//            for (int _cIndex = 0; _cIndex < _cSize; ++_cIndex)
//            {
//                ClipperLib::IntPoint _point{};
//                _point.X = (ClipperLib::cInt)(_in[_rIndex][_cIndex].x * PRECISION);
//                _point.Y = (ClipperLib::cInt)(_in[_rIndex][_cIndex].y * PRECISION);
//                _polyline.push_back(_point);
//            }
//            if (!_polyline.empty())
//                _out.push_back(_polyline);
//        }
//
//        if (!_out.empty())
//        {
//            ClipperLib::Clipper _clipperObject;
//            _clipperObject.AddPaths(_out, ClipperLib::ptSubject, true);
//
//            // Since Hatches now contains only two points, we wrap it in a Paths container
//            ClipperLib::Paths hatchPath = {Hatches};
//            _clipperObject.AddPaths(hatchPath, ClipperLib::ptClip, true);
//
//            _clipperObject.Execute(ClipperLib::ctUnion, _out, ClipperLib::pftEvenOdd, ClipperLib::pftEvenOdd);
//            _clipperObject.Clear();
//        }
//        return _out; 
//    }
//    catch (std::exception& ex) // Catch by reference to avoid slicing
//    {
//        std::string er = ex.what();
//        std::string error = "Conversion error:\t" + er;
//        throw std::exception(error.c_str());
//    }
//}



//this fn works
//taking all the vectors as input in one time as hatches
ClipperLib::Paths UnionofContourHatches(Contour& _in, ClipperLib::Paths Hatches)
{
    try
    {
        ClipperLib::Paths result;
        ClipperLib::Paths _out;
        int _rSize = (int)_in.size();
       
        for (int _rIndex = 0; _rIndex < _rSize; ++_rIndex)
        {
            ClipperLib::Path _polyline{};
            int _cSize = (int)_in[_rIndex].size();
            for (int _cIndex = 0; _cIndex < _cSize; ++_cIndex)
            {
                ClipperLib::IntPoint _point{};
                _point.X = (ClipperLib::cInt)(_in[_rIndex][_cIndex].x * PRECISION);
                _point.Y = (ClipperLib::cInt)(_in[_rIndex][_cIndex].y * PRECISION);
                _polyline.push_back(_point);
            }
            if (!_polyline.empty())
                _out.push_back(_polyline);
        }
        if (!_out.empty())
        {
            ClipperLib::Clipper _clipperObject;
            _clipperObject.AddPaths(_out, ClipperLib::ptClip, true);
            _clipperObject.AddPaths(Hatches, ClipperLib::ptSubject, false);
          //  _clipperObject.AddPaths(ClipperLib::Paths{}, ClipperLib::ptClip, true);
            ClipperLib::PolyTree soln;
            _clipperObject.Execute(ClipperLib::ctIntersection, soln);
            //_clipperObject.Execute(ClipperLib::ctUnion, _out, ClipperLib::pftNonZero, ClipperLib::pftNonZero);
            _clipperObject.Clear();
            
            ClipperLib::PolyTreeToPaths(soln, result);
        }
        if (!result.empty()) {
           // cout << "ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd";
        }
        return result; 
    }
    catch (std::exception ex)
    {
        std::string er = ex.what();
        std::string error = "Conversion error:\t" + er;
        throw std::exception(error.c_str());
    }
    return ClipperLib::Paths();
}



ClipperLib::Paths ConvertContourToClipperPaths(const Contour& contour) {
    ClipperLib::Paths paths;
    for (const auto& polyline : contour) {
    ClipperLib::Path path;
    for (const auto& point : polyline) {
        path.push_back(ClipperLib::IntPoint(static_cast<ClipperLib::cInt>(point.x * PRECISION), static_cast<ClipperLib::cInt>(point.y * PRECISION)));
    }
     paths.push_back(path);
    }
    return paths;
}


ClipperLib::Paths ClipVectorWithContour(const Contour& contour, const ClipperLib::Path& vector) {
    ClipperLib::Paths contourPaths = ConvertContourToClipperPaths(contour);
    ClipperLib::Clipper clipper;

    clipper.AddPaths(contourPaths, ClipperLib::ptSubject, false);
    ClipperLib::Paths vectorPath = { vector };
    clipper.AddPaths(vectorPath, ClipperLib::ptClip, true);
   // clipper.AddPath(vector, ClipperLib::ptClip, true);

    ClipperLib::Paths solution;
    clipper.Execute(ClipperLib::ctIntersection, solution, ClipperLib::pftEvenOdd, ClipperLib::pftEvenOdd);

    return solution;
}

void DrawClippedVector(cv::Mat& image, const ClipperLib::Paths& clippedVector, double scale , int sideLength , int baseplatesize) {
    for (const auto& path : clippedVector) {
        for (size_t i = 0; i < path.size() - 1; ++i) {
            cv::Point pt1(static_cast<float>(path[i].X / scale), static_cast<float>(path[i].Y / scale));
            cv::Point pt2(static_cast<float>(path[i + 1].X / scale), static_cast<float>(path[i + 1].Y / scale));
            Point2f convertpt1 = convertcordinates(pt1.x, pt1.y, sideLength, baseplatesize);
            Point2f convertpt2 = convertcordinates(pt2.x, pt2.y, sideLength, baseplatesize);
            cv::line(image, convertpt1, convertpt2, cv::Scalar(255, 0, 0), 1); // Draw line in blue color
            //cv::Scalar color(0, 0, 0); // black color
            //cv::circle(image, convertpt1, 1, color, -1);
            //cv::circle(image, convertpt2, 1, color, -1);
        }
    }
}



//ClipperLib::Paths clipvectorwithcontour(const Contour& _in, const ClipperLib::Path& vector)
//{
//    try
//    {
//        ClipperLib::Paths _out{};
//        int _rSize = (int)_in.size();
//       
//        for (int _rIndex = 0; _rIndex < _rSize; ++_rIndex)
//        {
//            ClipperLib::Path _polyline{};
//            int _cSize = (int)_in[_rIndex].size();
//            for (int _cIndex = 0; _cIndex < _cSize; ++_cIndex)
//            {
//                ClipperLib::IntPoint _point{};
//                _point.X = (ClipperLib::cInt)(_in[_rIndex][_cIndex].x * PRECISION);
//                _point.Y = (ClipperLib::cInt)(_in[_rIndex][_cIndex].y * PRECISION);
//                _polyline.push_back(_point);
//            }
//            if (!_polyline.empty())
//                _out.push_back(_polyline);
//        }
//        if (!_out.empty())
//        {
//            ClipperLib::Clipper _clipperObject;
//            _clipperObject.AddPaths(_out, ClipperLib::ptSubject, true);
//            ClipperLib::Paths vectorPath = { vector };
//            _clipperObject.AddPaths(vectorPath, ClipperLib::ptClip,  true);
//          //  _clipperObject.AddPath(vector, ClipperLib::ptClip, true);
//           // _clipperObject.AddPaths(ClipperLib::Paths{}, ClipperLib::ptClip, true);
//            _clipperObject.Execute(ClipperLib::ctIntersection, _out, ClipperLib::pftEvenOdd, ClipperLib::pftEvenOdd);
//
//            _clipperObject.Clear();
//        }
//        return _out; 
//    }
//    catch (std::exception ex)
//    {
//        std::string er = ex.what();
//        std::string error = "Conversion error:\t" + er;
//        throw std::exception(error.c_str());
//    }
//    return ClipperLib::Paths();
//}



//ClipperLib::Paths clipvectorwithcontour(const Contour& _in, const ClipperLib::Path& vector) {
//    try {
//        ClipperLib::Paths contourPaths;
//        for (const auto& polyline : _in) {
//            ClipperLib::Path clipperPath;
//            for (const auto& point : polyline) {
//                clipperPath.push_back(ClipperLib::IntPoint(
//                    static_cast<ClipperLib::cInt>(point.x * PRECISION),
//                    static_cast<ClipperLib::cInt>(point.y * PRECISION)
//                ));
//            }
//            if (!clipperPath.empty()) {
//                contourPaths.push_back(clipperPath);
//            }
//        }
//
//        ClipperLib::Clipper clipper;
//        clipper.AddPaths(contourPaths, ClipperLib::ptSubject, true); // Assuming contours are closed paths
//        ClipperLib::Paths vectorPaths = { vector }; // Assuming the vector is an open path but added as closed for clipping
//        clipper.AddPaths(vectorPaths, ClipperLib::ptClip, true); // Even if vector is conceptually open, Clipper treats paths as closed
//
//        ClipperLib::Paths result;
//        clipper.Execute(ClipperLib::ctIntersection, result, ClipperLib::pftEvenOdd, ClipperLib::pftEvenOdd);
//        return result;
//    }
//    catch (const std::exception& ex) {
//        std::cerr << "Exception caught in ClipVectorWithContour: " << ex.what() << std::endl;
//        throw; // Rethrow the caught exception
//    }
//}







//ClipperLib::Paths CreateThinPolygonsFromLines(const ClipperLib::Paths& lines, double thickness)
//{
//    ClipperLib::Paths thinPolygons;
//
//    for (const auto& line : lines)
//    {
//        for (size_t i = 0; i < line.size() - 1; ++i)
//        {
//            // Calculate the direction vector of the line segment
//            double dx = static_cast<double>(line[i + 1].X - line[i].X);
//            double dy = static_cast<double>(line[i + 1].Y - line[i].Y);
//
//            // Calculate the length of the direction vector
//            double length = std::sqrt(dx * dx + dy * dy);
//
//            // Calculate the normalized perpendicular vector
//            double perpX = -dy / length;
//            double perpY = dx / length;
//
//            // Calculate the offset for both sides of the line segment
//            double offsetX = perpX * (thickness / 2.0) * PRECISION;
//            double offsetY = perpY * (thickness / 2.0) * PRECISION;
//
//            // Create the thin polygon (rectangle) by offsetting the line segment
//            ClipperLib::Path polygon;
//            polygon.push_back(ClipperLib::IntPoint(line[i].X + offsetX, line[i].Y + offsetY));
//            polygon.push_back(ClipperLib::IntPoint(line[i + 1].X + offsetX, line[i + 1].Y + offsetY));
//            polygon.push_back(ClipperLib::IntPoint(line[i + 1].X - offsetX, line[i + 1].Y - offsetY));
//            polygon.push_back(ClipperLib::IntPoint(line[i].X - offsetX, line[i].Y - offsetY));
//
//            thinPolygons.push_back(polygon);
//        }
//    }
//
//    return thinPolygons;
//}
//
//const double HATCH_THICKNESS = 0.0001; // Example small thickness for hatches
//ClipperLib::Paths UnionofContourHatches(Contour& _in, ClipperLib::Paths hatches)
//{
//    try
//    {
//        ClipperLib::Paths result;
//
//        // Convert Contour to ClipperLib::Paths
//        ClipperLib::Paths contoursPaths;
//        for (const auto& contour : _in)
//        {
//            ClipperLib::Path path;
//            for (const auto& point : contour)
//            {
//                path.push_back(ClipperLib::IntPoint(
//                    static_cast<ClipperLib::cInt>(point.x * PRECISION),
//                    static_cast<ClipperLib::cInt>(point.y * PRECISION)));
//            }
//            contoursPaths.push_back(path);
//        }
//
//        // Expand hatch lines into thin polygons
//        ClipperLib::Paths expandedHatches = CreateThinPolygonsFromLines(hatches, HATCH_THICKNESS * PRECISION);
//
//        if (!contoursPaths.empty() && !expandedHatches.empty())
//        {
//            ClipperLib::Clipper clipper;
//            clipper.AddPaths(contoursPaths, ClipperLib::ptClip, true); // Assuming contours are closed polygons
//            clipper.AddPaths(expandedHatches, ClipperLib::ptSubject, true); // Now adding as closed polygons
//
//            ClipperLib::PolyTree intersectionPolyTree;
//            clipper.Execute(ClipperLib::ctUnion, intersectionPolyTree);
//
//            // Convert the resulting PolyTree to Paths
//            ClipperLib::PolyTreeToPaths(intersectionPolyTree, result);
//        }
//
//        return result;
//    }
//    catch (std::exception& ex)
//    {
//        std::string error = "Conversion error:\t" + std::string(ex.what());
//        throw std::runtime_error(error);
//    }
//    return ClipperLib::Paths();
//}

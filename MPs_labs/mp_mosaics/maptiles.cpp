/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<3>> locations;
    map<Point<3>, TileImage*> sourceMap; //declaring the tile positions and their source mapping
    for (auto iter = theTiles.begin(); iter != theTiles.end(); iter++) { 
        //iterate all tiles and map them to appropriate position
        LUVAPixel pixel = iter->getAverageColor(); //convert to avg color
        Point<3> point = convertToXYZ(pixel); //convert to xyz
        locations.push_back(point);
        sourceMap[point] = &*iter; //finish creating a good source map
    }
    KDTree<3> kdt(locations);
    MosaicCanvas* output = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    for (int i = 0; i < output->getRows(); i++) {
        for (int j = 0; j < output->getColumns(); j++) {
            //find the nearest neighbour and use map find the correct position
            Point<3> idx = kdt.findNearestNeighbor(convertToXYZ(theSource.getRegionColor(i,j)));
            output->setTile(i, j, sourceMap[idx]);
        }
    }

    return output;
}


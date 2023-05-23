#include "mainwindow.hpp"

#include <QApplication>

#include <qgsapplication.h>
#include <qgsproviderregistry.h>
#include <qgssinglesymbolrenderer.h>
#include <qgssymbol.h>
#include <qgsmaplayer.h>
#include <qgsvectorlayer.h>
#include <qgsrasterlayer.h>
#include <qgsmapcanvas.h>
#include <qgsmapcanvasutils.h>
#include <qgsmaplayeractionregistry.h>
#include <qgsstatusbar.h>

#include <QLayout>
#include <QVBoxLayout>
#include <QMainWindow>

//
// Qt Includes
//
#include <QString>
#include <QApplication>
#include <QWidget>
#include <QStatusBar>

#ifdef CORE_EXPORT
int  a;
#endif

int main(int argc, char ** argv)
{
	// Start the Application
	QgsApplication app(argc, argv, true);

	QMainWindow * win = new QMainWindow();

	//QApplication app(argc, argv);
	QString myPluginsDir        = "/usr/lib/qgis/plugins/";
	QString myLayerPath         = "/home/nsushenkov/Desktop/25/probnik.shp";
	QString myLayerBaseName     = "Brasil_Cap";
	QString myProviderName      = "ogr";
	// Instantiate Provider Registry
	QgsProviderRegistry::instance(myPluginsDir);
	// create a maplayer instance
	QgsVectorLayer * mypLayer =
			new QgsVectorLayer(myLayerPath, myLayerBaseName, myProviderName);

	QgsRasterLayer * tifLayer = new QgsRasterLayer("/home/nsushenkov/Desktop/25/big.tif");

	if (mypLayer->isValid())
	{
		qDebug("v Layer is valid");
	}
	else
	{
		qDebug("v Layer is NOT valid");
	}

	if (tifLayer->isValid())
	{
		qDebug("r Layer is valid");
	}
	else
	{
		qDebug("r Layer is NOT valid");
	}

	QgsSingleSymbolRenderer *mypRenderer = new QgsSingleSymbolRenderer(QgsSymbol::defaultSymbol(mypLayer->geometryType()));

	mypLayer->setRenderer(mypRenderer);

	QList<QgsMapLayer*> myLayerSet;

	myLayerSet.append(mypLayer);
	myLayerSet.append(tifLayer);

	// Create the Map Canvas
	QgsMapCanvas * mypMapCanvas = new QgsMapCanvas();
	mypMapCanvas->setExtent(tifLayer->extent());
	//  mypMapCanvas->enableAntiAliasing(true);
	mypMapCanvas->setCanvasColor(QColor(0, 255, 255));
	//  mypMapCanvas->freeze(false);
	//  // Set the Map Canvas Layer Set
	mypMapCanvas->setLayers(myLayerSet);
	mypMapCanvas->setVisible(true);
	mypMapCanvas->refresh();

	QgsStatusBar * stBar = new QgsStatusBar();

	QStatusBar * bar = new QStatusBar;

	win->setCentralWidget(mypMapCanvas);
	win->setStatusBar(new QStatusBar(stBar));

	win->show();

	// Start the Application Event Loop
	return app.exec();
}

// place your code here

#include <QApplication>
#include <QString>
#include <QMap>
#include <QDir>
#include <QImage>
#include <QTime>
#include <QPainter>
#include <QFont>
#include <QPaintDevice>

#include <iostream>
#include <math.h>

// #include "seakgObjects2D.h"

/*
template<typename T>
void forForPixels(QImage &inputImage, QImage &outputImage, T &t)
{
	std::cout << t.name().toStdString() << " # Process completed: ";
	int countpixels = inputImage.width() * inputImage.height();
	int comleted = 0;
	int procent = -1;
	
	for(int x = 0; x < inputImage.width(); x++)
	{
		for(int y = 0; y < inputImage.height(); y++)
		{
			t.process(inputImage, outputImage, x, y);
			
			comleted++;
			int tempProcent = (double(comleted) / double(countpixels)) * 100;
			if( tempProcent != procent)
			{
				procent = tempProcent;
				std::cout << "\r" << t.name().toStdString() << " # Process completed: " << tempProcent << " %";
			}
		}
	}
	
	std::cout << "\r" << t.name().toStdString() << " # Process completed: 100 %\n";
};
* */
// ---------------------------------------------------------------------------
/*
struct toWhiteBlack
{
	QString name() {
		 return "length";
	}
	
	void process(QImage &inputImage, QImage &outputImage, int x, int y)
	{
		QRgb pxlXY = inputImage.pixel(x,y);
		uint nGray = qGray(pxlXY);
		if(nGray > 128)
		{
			QRgb value;
			value = qRgb(255,255,255);
			outputImage.setPixel(x, y,value);
		}
		else
		{
			QRgb value;
			value = qRgb(0,0,0);
			outputImage.setPixel(x, y, value);
		};
	};
};
* */
// ---------------------------------------------------------------------------
/*
struct toObjects
{
	seakgObjects2D objects;
	
	QString name() {
		 return "objects";
	}
	
	void process(QImage &inputImage, QImage &outputImage, int x, int y)
	{
		QRgb pxlXY = inputImage.pixel(x,y);
		uint nGray = qGray(pxlXY);
		
		if(nGray > 128)
		{
			QRgb value;
			value = qRgb(255,255,255);
			outputImage.setPixel(x, y,value);
		}
		else
		{
			QRgb value;
			value = qRgb(0,0,0);
			outputImage.setPixel(x, y, value);
			objects.addPoint(x,y);
		};
	};
	
};
* */
// ---------------------------------------------------------------------------
/*
struct onlyFatObject
{
	onlyFatObject(seakgObject2D_XY object, int deltaX, int deltaY) 
	: 
		object(object), 
		deltaX(deltaX), 
		deltaY(deltaY)
	{
		
	};
	
	seakgObject2D_XY object;
	int deltaX;
	int deltaY;
	
	QString name() {
		 return "fat object";
	}
	
	void process(QImage &inputImage, QImage &outputImage, int X, int Y)
	{
		int newX = X + deltaX;
		int newY = Y + deltaY;
		
		if(newX < 0 || newX >= outputImage.width()) return;
		if(newY < 0 || newY >= outputImage.height()) return;
		
		if(object.contains(X,Y))
		{
			QRgb value = inputImage.pixel(X,Y);
			outputImage.setPixel(newX, newY, value);
		}
		else
		{
			QRgb value;
			value = qRgba(255,255,255, 0);
			outputImage.setPixel(newX, newY, value);
		};
	};
	
};
// ---------------------------------------------------------------------------
*/

int randInt(int low, int high)
{
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
};

int nWidth = 640;
int nHeight = 480;
int nSizeFont = 13;
int nCountCharsWidth;
int nCountCharsHeigth;
//QString fontname = "Arial";
QString fontname = "Monospace";


QString genNewMatrix()
{
	QString res = "";
	for(int y=0; y<nCountCharsHeigth; y++)
	{
		for(int x=0; x<nCountCharsWidth; x++)
		{
			res += QString::number(randInt(0,15),16);
		}
		res += "\r\n";
	}
	return res;
}

void createClip(int i, QString name)
{
	QImage outputImage( nWidth, nHeight, QImage::Format_RGB32);
	
	int nRad = 30;
	
	int X = randInt(nRad,nWidth-nRad);
	int Y = randInt(nRad,nHeight-nRad);

	QRectF rectangle(X - nRad, Y - nRad, nRad*2, nRad*2);
	
	QString number = QString::number(i);
	
	while(number.count() < 6)
		number = "0" + number;
		
	
	QPainter p(&outputImage);
	{
		QBrush brush( Qt::black, Qt::SolidPattern);
		QPen pen(Qt::black);
		p.setPen(pen);
		p.setBrush(brush);
		p.drawRect(0,0,outputImage.width(),outputImage.height());
	}
	
	/*{
		QBrush brush( Qt::red, Qt::SolidPattern);
		QPen pen(Qt::white);
		p.setPen(pen);
		p.setBrush(brush);
		p.drawEllipse(rectangle);
	}*/

	{
		
		// draw caption
		
		QString mtr = genNewMatrix();
		QFontMetrics fontMetrics(QFont(fontname, nSizeFont));
 		QRect rectText = fontMetrics.boundingRect(name);
 		
		p.setPen(QPen(Qt::white));
		p.setFont(QFont(fontname, nSizeFont));
		// QRect rect(0, outputImage.height() - rectText.height(), outputImage.width(), rectText.height());
		QRect rect(0, 0, outputImage.width(), outputImage.height());
		p.drawText(rect, Qt::AlignLeft, mtr);
		// p.drawRect(0,0,outputImage.width(),outputImage.height());
		
		// 
		
		
		QRect rect2((outputImage.width() - rectText.width())/2 - 30, (outputImage.height() - rectText.height()-20)/2, rectText.width() + 30, rectText.height() + 20);
		p.drawRect(rect2);
		p.drawText(rect2, Qt::AlignCenter, name);
		p.end();
	}
	

	outputImage.save("images/clip-"+number+".png");	
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	// Create seed for the random
	// That is needed only once on application startup
	QTime time = QTime::currentTime();
	qsrand((uint)time.msec());

	QDir dir("./");
	if(!QDir("images").exists())
		dir.mkdir("images");
	
	
	QFontMetrics fontMetrics(QFont(fontname, nSizeFont));
 	QRect rectText = fontMetrics.boundingRect("01");

 	nCountCharsWidth = (nWidth / (rectText.width()/2)) - 1;
	nCountCharsHeigth = (nHeight / (rectText.height()/2)) - 1;
	
	int countclips = (2*60+44) * 30;
	
	
	
	
	
	for(int i=0; i<countclips; i++)
	{
		if(i%200 == 0)
			std::cout << "\ti: " << i << "/" << countclips << "\r\n";
		
		createClip(i, "sea-kg - 01-Neuer (2013 Neuer)");
	}
	/*
	if( !test_seakgLine() ) return -1;
	if( !test_seakgRow() ) return -2;
	if( !test_seakgObject2D() ) return -3;
	if( !test_seakgObjects2D() ) return -4;
	
	//std::cout << "all test completed\n";
	
	//return 0;
	
	QString inputFileName, outputFileName;
	if(argc == 3)
	{
		inputFileName = QString(argv[1]);
		outputFileName = QString(argv[2]);
	}
	else 
		std::cout << "usage: cat-coin srcfilename dstfilename "<< std::endl;
		
	if (!inputFileName.isEmpty()) {
		
		QImage inputImage(inputFileName);
		if (inputImage.isNull()) {
			std::cout << "Error load image "<< std::endl;
			return 1;
		}
		
		QImage outputImage(inputImage.width(), inputImage.height(), QImage::Format_RGB32);
		//QImage outputImage(inputImage.width(), inputImage.height(), QImage::Format_ARGB32);
		
		std::cout << "inputImage.width = " << inputImage.width() << "\n";
		std::cout << "inputImage.height = " << inputImage.height() << "\n";
		
		//toWhiteBlack len;
		//forForPixels(inputImage, outputImage, len);
		
		int newWidth, newHeight;
		{
			toObjects toObjs;
			forForPixels(inputImage, outputImage, toObjs);
		
			toObjs.objects.refactoring();
		
			seakgObject2D_XY object = toObjs.objects.getMaxFattestOfObject();
			object.fillGaps();
			
			int X, Y;
			object.getCenterOfMass(X, Y);
			int minX_Y = object.getMinX(Y);
			int maxX_Y = object.getMaxX(Y);
			int minY_X = object.getMinY(X);
			int maxY_X = object.getMaxY(X);
			
			int xR = std::max(X - minX_Y, maxX_Y - X);
			int yR = std::max(Y - minY_X, maxY_X - Y);
			
			int R = (xR + yR) / 2;
			
			newWidth = R*2;
			newHeight = R*2;
			
			QRgb value;
			value = qRgb(128,128,128);
			
			QRectF rectangle(X - R, Y - R, R*2, R*2);
			
			std::cout << "minX_Y = " << minX_Y << "  minY_X = " << minY_X << "\n";
			std::cout << "maxX_Y = " << maxX_Y << "  maxY_X = " << maxY_X << "\n";
			QPainter p(&outputImage);
			
			{
				QBrush brush( Qt::white, Qt::SolidPattern);
				QPen pen(Qt::white);
				p.setPen(pen);
				p.setBrush(brush);
				p.drawRect(0,0,outputImage.width(),outputImage.height());
			}
			
			{
				QBrush brush( Qt::black, Qt::SolidPattern);
				QPen pen(Qt::black);
				p.setPen(pen);
				p.setBrush(brush);
				p.drawEllipse(rectangle);
			}
			
			//outputImage.save(outputFileName + "_2.png");
		}
		
		
		QImage outputImage2( newWidth ,newHeight, QImage::Format_ARGB32);

		{
			toObjects toObjs;
			forForPixels(outputImage, outputImage, toObjs);
			
			toObjs.objects.refactoring();
		
			seakgObject2D_XY fattestObject = toObjs.objects.getMaxFattestOfObject();
			fattestObject.fillGaps();
			
			// std::cout << "count : "
			
			int minX, maxX, minY, maxY;
			fattestObject.getExtremePoints(minX, maxX, minY, maxY);
			
			onlyFatObject fatObj(fattestObject, - minX, - minY);
			forForPixels(inputImage, outputImage2, fatObj);
		}
		// saves result
		outputImage2.save(outputFileName);
	}
	* */
	return 0;
}

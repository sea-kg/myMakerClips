// place your code here

#include <QApplication>
#include <QString>
#include <QMap>
#include <QDir>
#include <QImage>
#include <QTime>
#include <QPainter>
#include <QFont>
#include <QList>
#include <QPaintDevice>

#include <iostream>
#include <math.h>

// #include "seakgObjects2D.h"

int g_nWidth = 320;
int g_nHeight = 240;

int g_nBG_Color = 0x7175b0;

// ---------------------------------------------------------------------------

int randInt(int low, int high)
{
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
};

// ---------------------------------------------------------------------------

class forkMap
{
	public: 
		forkMap(double x, double y, double w);
		double x, y, w;
		int move_next(bool bLived);
		void print(QPainter &p);
		
		QList<forkMap *> childs;
};

// ---------------------------------------------------------------------------

forkMap::forkMap(double x, double y, double w) 
  : x(x), y(y), w(w) 
{

};

// ---------------------------------------------------------------------------

int forkMap::move_next(bool bLived)
{
	// std::cout << "move next \n";
	
	int max_count = 0;
	for(int i = 0; i < childs.count(); i++)
		max_count = max_count + childs[i]->move_next(bLived);

	if(max_count == 0) childs.clear();

	max_count++; // self
	
	if( bLived )
	{
		if(childs.count() > 2) return max_count;
		
		this->w = this->w + 1;
		double newChildW = (w - 1 / 3);
		if(newChildW < 2) return max_count;
		
		double newX, newY;
		int k_X1 = randInt(-1,1);
		int k_X2 = randInt(-1,1);
		int k_Y1 = randInt(-1,1);
		int k_Y2 = randInt(-1,1);
		
		newX = x + k_X1 * w + k_X2 * newChildW;
		newY = y + k_Y1 * w + k_Y2 * newChildW;
		
		if(newX < 0 || newX > g_nWidth || newY < 0 || newY > g_nHeight) return max_count;
		
		// std::cout << "\t" << k_X1 << "; " << k_X2 << "; " << k_Y1 << "; " << k_Y2 << "; \n";
		childs.push_back(new forkMap(newX, newY, newChildW));
		max_count++; // new child
	}
	else
	{
		// if(childs.count() > 2) return max_count;
		if(childs.count() < 2)
		{
			this->w = this->w - 3;
			if(this->w < 0)
			{
				childs.clear();
				this->w = 0;
				return max_count = max_count - 1;
			};
		};
	}
	return max_count;
};

// ---------------------------------------------------------------------------

void forkMap::print(QPainter &p)
{
	for(int i = 0; i < childs.count(); i++)
		childs[i]->print(p);

	QRectF rectangle(x - w, y - w, w*2, w*2);
	{
		QBrush brush( 0x70748d /*Qt::black*/, Qt::SolidPattern);
		QPen pen(0x2c2f48 /*Qt::white*/);
		p.setPen(pen);
		p.setBrush(brush);
		p.drawEllipse(rectangle);
	};
};

// ---------------------------------------------------------------------------

class treeMap 
{
	public:
		treeMap(int w, int h);
		~treeMap();
	
		void move_next();
		void saveToFile(QString filename);
		QString Caption;
		bool m_bLived1;
		bool m_bLived2;
	private:
	
		int m_nWidth, m_nHeight;
		forkMap *root1;
		forkMap *root2;
		
		int m_nSizeFont;
		int m_nCountCharsWidth;
		int m_nCountCharsHeigth;
		QString m_strFontname;
};

// ---------------------------------------------------------------------------

treeMap::treeMap(int w, int h) 
  : m_nWidth(w), m_nHeight(h), root1(NULL), root2(NULL)
{
	m_nSizeFont = 13;
	m_strFontname = "Monospace";
	// m_strFontname = "Arial";
	
	// calculate caption;
	QFontMetrics fontMetrics(QFont(m_strFontname, m_nSizeFont));
 	QRect rectText = fontMetrics.boundingRect("01");

 	m_nCountCharsWidth = (m_nWidth / (rectText.width()/2)) - 1;
	m_nCountCharsHeigth = (m_nHeight / (rectText.height()/2)) - 1;
};

// ---------------------------------------------------------------------------

treeMap::~treeMap()
{
	delete root1;
	delete root2;
};

// ---------------------------------------------------------------------------

void treeMap::move_next()
{
	if(root1 == NULL)
		root1 = new forkMap(double(randInt(m_nWidth/5, 4*m_nWidth/5)),double(randInt(m_nHeight/5, 4*m_nHeight/5)), 10);
		
	if(root2 == NULL)
		root2 = new forkMap(double(randInt(m_nWidth/5, 4*m_nWidth/5)),double(randInt(m_nHeight/5, 4*m_nHeight/5)), 10);
		
	// generic algorithm
	int max_count1 = root1->move_next(m_bLived1);
	int max_count2 = root2->move_next(m_bLived2);
	if(max_count1 == 0)
	{
		delete root1;
		root1 = NULL;
	}
	
	if(max_count2 == 0)
	{
		delete root2;
		root2 = NULL;
	}
	
	if(m_bLived1 && max_count1 > 5000)
		m_bLived1 = false;
	if(!m_bLived1 && max_count1 < 1)
		m_bLived1 = true;
			
	if(m_bLived2 && max_count2 > 5000)
		m_bLived2 = false;
	if(!m_bLived2 && max_count2 < 1)
		m_bLived2 = true;

	return;
};

// ---------------------------------------------------------------------------

void treeMap::saveToFile(QString filename)
{
	if(root1 == NULL)
		root1 = new forkMap(double(randInt(m_nWidth/5, 4*m_nWidth/5)),double(randInt(m_nHeight/5, 4*m_nHeight/5)), 10);
		
	if(root2 == NULL)
		root2 = new forkMap(double(randInt(m_nWidth/5, 4*m_nWidth/5)),double(randInt(m_nHeight/5, 4*m_nHeight/5)), 10);
		
	QImage outputImage(m_nWidth, m_nHeight, QImage::Format_RGB32);

	QPainter p(&outputImage);
	{
		QBrush brush( g_nBG_Color /*Qt::white*/, Qt::SolidPattern);
		QPen pen(g_nBG_Color /*Qt::white*/);
		p.setPen(pen);
		p.setBrush(brush);
		p.drawRect(0,0,outputImage.width(),outputImage.height());
	}
	
	root1->print(p);
	root2->print(p);
	
	{
		// draw caption
		
		// QString mtr = genNewMatrix();
		QFontMetrics fontMetrics(QFont(m_strFontname, m_nSizeFont));
 		QRect rectText = fontMetrics.boundingRect(Caption);
 		
 		QBrush brush( Qt::black, Qt::SolidPattern);
 		p.setBrush(brush);
		p.setPen(QPen(Qt::white));
		p.setFont(QFont(m_strFontname, m_nSizeFont));
		// QRect rect(0, outputImage.height() - rectText.height(), outputImage.width(), rectText.height());
		// QRect rect(0, 0, outputImage.width(), outputImage.height());
		// p.drawText(rect, Qt::AlignLeft, mtr);
		// p.drawRect(0,0,outputImage.width(),outputImage.height());	
		
		QRect rect2((outputImage.width() - rectText.width())/2 - 30, (outputImage.height() - rectText.height()-20)/2, rectText.width() + 30, rectText.height() + 20);
		p.drawRect(rect2);
		p.drawText(rect2, Qt::AlignCenter, Caption);
		p.end();
	}

	outputImage.save(filename);		
};

// ---------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QString caption = "sea-kg - 06-Possible (2013 Neuer)";
	for(int i = 0; i < argc; i++){
		if(i == 1){
			caption = QString(argv[i]);
		}
		
		if(i == 2){
			g_nBG_Color = QString(argv[i]).toInt(Q_NULLPTR, 16);
		}
	}
	
	// Create seed for the random
	// That is needed only once on application startup
	QTime time = QTime::currentTime();
	qsrand((uint)time.msec());

	int nWidth = 320;
	int nHeight = 240;
	QDir dir("./");
	if(!QDir("images").exists())
		dir.mkdir("images");

	treeMap tree(nWidth, nHeight );
	
	tree.Caption = caption;
	int countclips = 2*60 * 30;
	
	//max_count
	for(int i=0; i<countclips; i++)
	{
		if(i%30 == 0)
			std::cout << "\ti: " << i << "/" << countclips << "\r\n";
		
		QString number = QString::number(i);
		while(number.count() < 6)
			number = "0" + number;
				
		tree.saveToFile("images/clip-"+number+".png");
		tree.move_next();
		
		// std::cout << "\t" << max_count << "; Lived: " << (g_bLived ? "true" : "false" ) << "\n";
	};

	std::cout << "\t ::: >>> generated!!!!\n\n\n";
	return 0;
}

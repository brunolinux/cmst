/**************************** iconman.h  ******************************

Class to manage icons and allow the user to provide substitutions based
on the the system theme.

Copyright (C) 2015
by: Andrew J. Bibb
License: MIT

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"),to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
***********************************************************************/

# ifndef ICON_MANAGER
# define ICON_MANAGER

# include <QObject>
# include <QMap>
# include <QIcon>

# include "../resource.h"

struct IconElement
{
	QString resource_path;
	QString fdo_name;
	QMap <QString, QString> theme_map;
};

class IconManager : public QObject
{
  Q_OBJECT

  public:
  // members
    IconManager(QObject* parent);
    
  // functions
		QIcon getIcon(const QString&);
		QString getIconName(const QString&);
  
  private:
  // members
		QMap<QString, IconElement> icon_map; 
		QString cfg;
		QString qrc;
		
	// functions
		bool buildResourceIcon(QIcon&, const QString&);
		bool buildThemeIcon(QIcon&, const QString&);	
		QString getFallback(const QString&);
		void makeLocalFile();	
		QString extractValue(const QString&);
		QString extractKey(const QString&);
  
};
#endif

/**************************** roothelper.cpp ***************************

Code for the root helper registered on DBus.  When registered the CMST
provisioning editor will communicate with object using signals.  As the
name implies roothelper is run as the root user, since we need to read
and write to /var/lib/connman. This program is started by DBus and the
configuration files necessary to make that happen are in the system dir.

Copyright (C) 2013-2014
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

# include <QtCore/QDebug>
# include <QtDBus/QDBusConnection>
# include <QDir>

#	include "./roothelper.h"

//	header files generated by qmake from the xml file created by qdbuscpp2xml
# include "roothelper_adaptor.h"
# include "roothelper_interface.h"

//	constructor
RootHelper::RootHelper(QObject* parent)
    : QObject(parent)
{
	//	Create RootHelperadaptor  
	new RoothelperAdaptor(this);	
	
	// Data members
	b_connected = false;
	
	return;
}  
		
///////////////////// Public Slots /////////////////////////////////////
//
// Slot to start the event loop
void RootHelper::startHelper()
{
		// Try to register a service on the system bus
	if (! QDBusConnection::systemBus().registerService("org.cmst.roothelper")) {
		qDebug() << tr("Failed to register service org.cmst.roothelper - there may be another instance running.");
		QCoreApplication::instance()->exit(1);
	}
	
	// try to register an object on the system bus
		if (! QDBusConnection::systemBus().registerObject("/", this)) {
			qDebug() << tr("Failed to register roothelper object on the system bus.");
			QCoreApplication::instance()->exit(2);
	}

	// if we made it this far we have a connection and are registered on the system bus.
	b_connected = true;

	return;
}

//
// Slot to select the file to read
void RootHelper::getFileList()
{	
	// variables
	QDir dir = QDir("/var/lib/connman");
	QStringList filters;
	filters << "*.conf";

	// get a list of all conf files and return it
	emit readCompleted(dir.entryList(filters, QDir::Files, QDir::Name | QDir::Reversed) );
	
	return;
}

//
// Slot to write the file to disk
void RootHelper::saveFile()
{
	qDebug() << "inside save file";
	
	return;
}

////////////////////// Private Functions ///////////////////////////////
//


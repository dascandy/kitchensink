/**********************************************************************
*
* Copyright (c) 2012-2017 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#include "util.h"
#include "videoplayer.h"
#include "videowidget.h"

#include <QGroupBox>
#include <QtMultimedia>

VideoPlayer::VideoPlayer(QWidget *parent)
   : QWidget(parent), m_surface(0)
{
   setWindowTitle(tr("Video Widget"));

   //
   QGroupBox *groupBox = new QGroupBox(tr("Send Email"));
   QFont font = groupBox->font();
   font.setPointSize(10);
   groupBox->setFont(font);

   QLabel *labelTo = new QLabel(tr("To:"));
   labelTo->setFont(font);

   QLineEdit *e_to = new QLineEdit();
   e_to->setFont(font);

   QLabel *labelSubject = new QLabel(tr("Subject:"));
   labelSubject->setFont(font);

   QLineEdit *e_subject = new QLineEdit();
   e_subject->setFont(font);

   QLabel *labelBody = new QLabel(tr("Body:"));
   labelBody->setFont(font);

   QTextEdit *e_body = new QTextEdit();
   e_body->setFont(font);

   //
   QPushButton *close_PB  = new QPushButton(tr("Close"));
   close_PB->setFont(font);

   //
   VideoWidget *videoWidget = new VideoWidget;
   m_surface = videoWidget->videoSurface();

   QGridLayout *gLayout = new QGridLayout;
   gLayout->addWidget(labelTo,0,0);
   gLayout->addWidget(e_to,0,1);
   gLayout->addWidget(labelSubject,1,0);
   gLayout->addWidget(e_subject,1,1);
   gLayout->addWidget(labelBody, 2, 0);
   gLayout->addWidget(e_body, 2, 1, 1, 2);
   gLayout->addWidget(videoWidget, 0, 2, 2, 1);
   groupBox->setLayout(gLayout);

   QHBoxLayout *bottomLayout2 = new QHBoxLayout;
   bottomLayout2->addStretch();
   bottomLayout2->addWidget(close_PB);
   bottomLayout2->addStretch();

   QBoxLayout *mainLayout = new QVBoxLayout;
   mainLayout->addWidget(groupBox);
   mainLayout->addSpacing(8);
   mainLayout->addLayout(bottomLayout2);

   mainLayout->setContentsMargins(14,14,14,9);
   setLayout(mainLayout);

   // load data from resource file
   QString fileName = ":/resources/email_3.gif";

   if (! fileName.isEmpty()) {
      m_surface->stop();

      m_movie.setFileName(fileName);

      if (! m_movie.isValid()) {
         ksMsg("Image is invalid and will not be displayed.");
      }

      m_movie.jumpToFrame(0);
      m_movie.start();

   }

   // signals
   connect(&m_movie, SIGNAL(stateChanged(QMovie::MovieState)), this, SLOT(stateChanged(QMovie::MovieState)));
   connect(&m_movie, SIGNAL(frameChanged(int)), this, SLOT(frameChanged(int)));
   connect(close_PB, SIGNAL(clicked()), this, SLOT(actionClose()));
}

VideoPlayer::~VideoPlayer()
{
}

void VideoPlayer::stateChanged(QMovie::MovieState state)
{
   // not used in this example, left here for reference
   switch(state) {
      case QMovie::NotRunning:
         break;

      case QMovie::Paused:
         break;

      case QMovie::Running:

         break;
   }
}

void VideoPlayer::frameChanged(int frame)
{
   if (! presentImage(m_movie.currentImage())) {
      m_movie.stop();
      ksMsg("Unable to display image.");
   }
}

bool VideoPlayer::presentImage(const QImage &image)
{
   QVideoFrame frame(image);

   if (! frame.isValid()) {
      return false;
   }

   QVideoSurfaceFormat currentFormat = m_surface->surfaceFormat();

   if (frame.pixelFormat() != currentFormat.pixelFormat()
         || frame.size() != currentFormat.frameSize()) {

      QVideoSurfaceFormat format(frame.size(), frame.pixelFormat());

      if (! m_surface->start(format)) {
         return false;
      }
   }

   if (! m_surface->present(frame)) {
      m_surface->stop();
      return false;

   } else {
      return true;

   }
}

void VideoPlayer::actionClose() {
   this->parentWidget()->close();
}
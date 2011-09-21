/*=========================================================================

   Program: ParaView
   Module:    pqCalculatorSummaryPanel.h

   Copyright (c) 2005-2008 Sandia Corporation, Kitware Inc.
   All rights reserved.

   ParaView is a free software; you can redistribute it and/or modify it
   under the terms of the ParaView license version 1.2.

   See License_v1.2.txt for the full ParaView license.
   A copy of this license can be obtained by contacting
   Kitware Inc.
   28 Corporate Drive
   Clifton Park, NY 12065
   USA

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
#include "pqCalculatorSummaryPanel.h"

#include <QFormLayout>
#include <QLineEdit>

#include "pqProxy.h"
#include "pqSMAdaptor.h"

pqCalculatorSummaryPanel::pqCalculatorSummaryPanel(pqProxy *proxy, QWidget *parent)
  : pqObjectPanel(proxy, parent)
{
  QFormLayout *layout = new QFormLayout;

  this->Expression = new QLineEdit(this);
  this->ResultArrayName = new QLineEdit(this);

  // set default array name to 'Result'
  this->ResultArrayName->setText("Result");

  layout->addRow("Expression:", this->Expression);
  layout->addRow("Result Array Name:", this->ResultArrayName);

  vtkSMProxy *smProxy = proxy->getProxy();

  this->Links.setUseUncheckedProperties(true);
  this->Links.addPropertyLink(this->Expression,
                              "currentText",
                              SIGNAL(currentTextChanged(const QString&)),
                              smProxy,
                              smProxy->GetProperty("Function"));

  this->Links.addPropertyLink(this->ResultArrayName,
                              "currentText",
                              SIGNAL(currentTextChanged(const QString&)),
                              smProxy,
                              smProxy->GetProperty("ResultArrayName"));

  setLayout(layout);
}

pqCalculatorSummaryPanel::~pqCalculatorSummaryPanel()
{
}

void pqCalculatorSummaryPanel::accept()
{
  this->pqObjectPanel::accept();

  this->Links.accept();
}

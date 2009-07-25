/****************************************************************************
**
** This file is part of the pSketcher project.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** Copyright (C) 2006-2008 Michael Greminger. All rights reserved.
**
****************************************************************************/

#include <sstream>

#include "ConstraintEquationBase.h"
#include "pSketcherModel.h"

using namespace std;

void ConstraintEquationBase::ApplySelectionMask(SelectionMask mask)
{
	if(mask == All || mask == Constraints)
		SetSelectable(true);
	else
		SetSelectable(false);
}

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

#ifndef VectorH
#define VectorH

#include "PrimitiveBase.h"

// vector class
class Vector : public PrimitiveBase
{
	public:
		Vector ( double x, double y, double z, bool x_free = false, bool y_free = false, bool z_free = false);
		//Vector ( DOFPointer x, DOFPointer y, DOFPointer z );
		mmcMatrix GetmmcMatrix();  // returns mmcMatrix vector containing current location 

		void ApplySelectionMask(SelectionMask mask);

	private:
		DOFPointer x_;
		DOFPointer y_;
		DOFPointer z_;
};
typedef boost::shared_ptr<Vector> VectorPointer;



#endif //VectorH

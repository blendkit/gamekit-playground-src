//
// Copyright (c) 2013 MASA Group recastdetour@masagroup.net
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#ifndef SCENECREATOR_H
#define SCENECREATOR_H

#include "CrowdSample.h"
#include "InputGeom.h"
#include "NavMeshCreator.h"
#include "BuildContext.h"

#include <DetourCrowd.h>
#include <DetourNavMeshQuery.h>


/// This class is used to create a complete scene (navigation mesh and agents) 
/// from a file.
class dtSceneCreator
{
public:
    dtSceneCreator();
    ~dtSceneCreator();
    
	/// Load informations from the given file.
	bool createFromFile(const char* fileName);
	bool createFromBuffer(const char* buffer);

	/// Initialize the scene, the navigation mesh and the crowd.
    bool initialize(InputGeom* scene, dtNavMesh* navMesh, dtCrowd* crowd);
	CrowdSample m_currentSample;
        
private:
	dtBuildContext m_context; /// rcContext concrete implementation
};

#endif
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Bentley.Interop.MicroStationDGN;
using BD = Bentley.DgnPlatformNET;

namespace CppAddinTest
{
    class KeyinCommands
    {
        public static void Command(string unparsed)
        {
            //cppAddin.KeyinCommands.Command("");
            //PDIWTCodeQueryLib.MeshTest.ConstructMesh();
            //PDIWTCodeQueryLib.MeshTest.DgnFileTest();
            //PDIWTCodeQueryLib.MeshTest.DgnModel();
            BD.DgnFile activeDgnFile = Program.GetActiveDgnFile();
            BD.LevelCache levelCache = activeDgnFile.GetLevelCache();
            foreach (var level in levelCache.GetHandles())
            {
                BD.LevelDefinitionColor byLevelColor = level.GetByLevelColor();
                var colorinfo = BD.DgnColorMap.ExtractElementColorInfo(byLevelColor.Color, activeDgnFile);
                
            }
        }
    }
}

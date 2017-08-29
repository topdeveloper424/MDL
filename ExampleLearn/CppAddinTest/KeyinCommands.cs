using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Bentley.Interop.MicroStationDGN;
using PDIWTCodeQueryLib;
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

            PDIWTCodeQueryLib.CellFunction cellFunction = new CellFunction(@"D:\项目\BIM实习\梅山二期\建模中间文件\码头\celllib\节点库.cel");
            if (BD.StatusInt.Success == cellFunction.AttachLibrary())
            {
                MessageBox.Show("DONE!");
            }
        }
    }
}

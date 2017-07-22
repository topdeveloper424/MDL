using System;
using System.Collections.Generic;
using System.Linq;
using System.Resources;
using System.Text;
using System.Threading.Tasks;

using BCOM = Bentley.Interop.MicroStationDGN;
using BD = Bentley.DgnPlatformNET;
using BM = Bentley.MstnPlatformNET;

namespace CppAddinTest
{

    [BM.AddIn(MdlTaskID = "CppAddinTest")]
    internal sealed class Program : BM.AddIn
    {
        public static Program Addin = null;
        private Program(IntPtr mdlDesc) : base(mdlDesc)
        {
            Addin = this;
        }
        protected override int Run(string[] commandLine)
        {
            ReloadEvent += new ReloadEventHandler(CppAddinTest_ReloadEvent);
            UnloadedEvent += new UnloadedEventHandler(CppAddinTest_UnloadedEvent);
            return 0;
        }
        protected override void OnUnloading(UnloadingEventArgs eventArgs)
        {
            base.OnUnloading(eventArgs);
        }
        private void CppAddinTest_ReloadEvent(BM.AddIn sender, ReloadEventArgs eventArgs)
        {

        }
        private void CppAddinTest_UnloadedEvent(BM.AddIn sender, UnloadedEventArgs eventArgs)
        {

        }
        //
        public static BD.DgnFile GetActiveDgnFile() => BM.Session.Instance.GetActiveDgnFile();
        public static BD.DgnModelRef GetActiveDgnModelRef() => BM.Session.Instance.GetActiveDgnModelRef();
        public static BD.DgnModel GetActiveDgnModel() => BM.Session.Instance.GetActiveDgnModel();

        public static BCOM.Application COM_App
        {
            get
            {
                return BM.InteropServices.Utilities.ComApp;
            }
        }
        //private static ResourceManager resourceManager
        //{
        //    get
        //    {
        //        return Properties.Resources.ResourceManager;
        //    }
        //}
    }
}

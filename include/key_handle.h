#ifndef _key_handle_h_
#define _key_handle_h_
namespace gelib{
	class AFX_EXT_CLASS Key_Handle{
		protected:
			~Key_Handle() {}
		public:
			void OnKeyDown(UINT nChar,UINT nRepCnt,UINT nFlags);
		};
}
#endif
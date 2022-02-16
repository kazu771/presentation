//=============================================================================
// 画像まとめたヘッダー[assetnames.h]
// date:2021/08/27  name:Kazuki Wada
//=============================================================================


//--------------------------------------------------------------
// 使用するテクスチャーたち
//--------------------------------------------------------------
#define ASSET_TITLELOGO   "asset/texture/Titles.png"      //タイトルロゴ
#define ASSET_PUSHLOGO    "asset/texture/Enter.png"       //Enterロゴ
#define ASSET_GAMELOGO    "asset/texture/GameLogo.png"    //ゲームロゴ
#define ASSET_HANDLOGO    "asset/texture/hand.png"        //ポインターロゴ
#define ASSET_FADE        "asset/texture/fade.png"        //フェード
#define ASSET_RULELOGO	  "asset/texture/rulelogo.png"	  //ルールロゴ
#define ASSET_RULE        "asset/texture/Rules.png"        //ルール
#define ASSET_EXPLOGO     "asset/texture/endexp.png"      //説明ロゴ
#define ASSET_EXP         "asset/texture/Explainss.png"         //説明
#define ASSET_END         "asset/texture/Ends.png"         //終了ロゴ
#define ASEET_EMPTYHEART  "asset/texture/EmptyHeart.png"  //体力用空のハート
#define ASSET_HEART       "asset/texture/Heart.png"       //体力用ハート
#define ASSET_POISON      "asset/texture/PoisonUi.png"    //毒
#define ASSET_NORMAL      "asset/texture/Arrow.png"       //通常の矢
#define ASSET_DOUBLE      "asset/texture/DoubleArrow.png" //二つ同時にでる矢
#define ASSET_DAMAGE      "asset/texture/Arrow.png"       //ダメージ用の数字
#define ASSET_TWOWAY      "asset/texture/twoway.png"      //二方向の矢
#define ASSET_CONFUSE     "asset/texture/Confusion.png"   //混乱テクスチャー
#define ASEET_CHARGEBAR   "asset/texture/chargebar.png"   //チャージバー用
#define ASEET_BACKCOLOR   "asset/texture/back.png"		  //背景カラー
#define ASSET_FIRST       "asset/texture/Title.png"
#define ASEET_CEAR		  "asset/texture/gameclear.png"    //クリア画面
#define ASEET_GAMEOVER    "asset/texture/gameovers.png"    //ゲームオーバー画面
#define ASSET_WHITEPUSH   "asset/texture/whitePush.png"    //白Enter

//テクチャーの名前
static const char* g_TextureFileName[] = {

	ASSET_TITLELOGO,
	ASSET_PUSHLOGO,
	ASSET_GAMELOGO,
	ASSET_HANDLOGO,
	ASSET_FADE,
	ASSET_RULELOGO,
	ASSET_RULE,
	ASSET_EXPLOGO,
	ASSET_EXP,
	ASEET_EMPTYHEART,
	ASSET_HEART,
	ASSET_POISON,
	ASSET_NORMAL,
	ASSET_DOUBLE,
	ASSET_DAMAGE,
	ASSET_TWOWAY,
	ASSET_CONFUSE,
	ASEET_CHARGEBAR,
	ASSET_END,
	ASEET_BACKCOLOR,
	ASSET_FIRST,
	ASEET_CEAR,
	ASEET_GAMEOVER,
	ASSET_WHITEPUSH,
};

//---------------
//列挙型宣言
//----------------
enum {

	TX_TLOGO,
	TX_PUSH,
	TX_GLOGO,
	TX_HAND,
	TX_FADE,
	TX_RULEROGO,
	TX_RULE,
	TX_EXPLOGO,
	TX_EXP,
	TX_EMPTY,
	TX_HEART,
	TX_POISON,
	TX_NORMAL,
	TX_DOUBLE,
	TX_DAMAGE,
	TX_TWOWAY,
	TX_CONFUSE,
	TX_CHARGEBAR,
	TX_END,
	TX_BACK,
	TX_FIRST,
	TX_CLEAR,
	TX_GAMEOVER,
	TX_WPUSH,
	TX_MAX

};




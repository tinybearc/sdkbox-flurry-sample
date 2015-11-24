
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        /////////////////////////////
        // 2. add a menu item with "X" image, which is clicked to quit the program
        //    you may modify it.
        // ask the window size
        var size = cc.winSize;

        var coinsLabel = cc.Label.createWithSystemFont("Hello Js", "Arial", 20);
        coinsLabel.setPosition(size.width/2, size.height*9/10);
        this.addChild(coinsLabel);

        cc.MenuItemFont.setFontName('arial');
        cc.MenuItemFont.setFontSize(32);

        var menu = new cc.Menu(
            new cc.MenuItemFont("clickme", this.onClicked, this)
            );
        menu.setPosition(size.width/2, size.height/2);
        menu.alignItemsVerticallyWithPadding(20);
        this.addChild(menu);

        this.session_created = false
        var self = this
        //init flurryanalytics
        sdkbox.PluginFlurryAnalytics.setListener({
            flurrySessionDidCreateWithInfo:function(info) {
                self.session_created = true
                var jsonInfo = JSON.parse(info)
                console.log("session started")
                console.log("APIKey :" + jsonInfo.apiKey + " session id :" + jsonInfo.sessionId);
                sdkbox.PluginFlurryAnalytics.logEvent("test event2 js", JSON.stringify({"eKey1":"eVal1", "eKey2":"eVal2"}));
            }
        });
        sdkbox.PluginFlurryAnalytics.init()
        // sdkbox.PluginFlurryAnalytics.startSession();

        return true;
    },
    onClicked: function() {
        if (this.session_created) {
            var ret = sdkbox.PluginFlurryAnalytics.logEvent("Test Event js");
            if (0 == ret) {
                console.log('log event failed');
            } else {
                console.log('log event successed')
            }
        } else {
            console.log("seesion havn't create");
        }
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});


